#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "TMySQLStatement.h"
#include "TSQLTableInfo.h"

#include "vtbl.h"
ClassImp(vtbl);

// struct which defines what tables can be handled.
const std::vector<struct VTBLS> vtbl::vtbls = {
    {"tblL3_Array_TriggerInfo", "tblL3_Array_TriggerInfo", 11},
    {"tblL3_Telescope_TriggerInfo", "tblL3_Telescope_TriggerInfo", 12},
    {"tblRun_Info", "tblRun_Info", 20}
};

TMySQLServer vtbl::server("mysql://romulus.ucsc.edu/VERITAS",
    "readonly", "");

vtbl::vtbl(std::string tblName_)
{
    std::vector<struct VTBLS>::const_iterator it =
        std::find_if(vtbl::vtbls.begin(), vtbl::vtbls.end(),
        [&tn = tblName_] (const struct VTBLS &v) -> bool
            { return v.tblName == tn; });

    if (it == vtbl::vtbls.end())
        throw std::invalid_argument("Unknown table name");

    tblName = tblName_;
    nFields = it->nFields;
    entry = 0;

    //std::cout << vtbl::server.ServerInfo() << std::endl;
}

vtbl::~vtbl()
{
    delete tree;
}

void vtbl::describe() const
{
    TSQLTableInfo *tableInfo = vtbl::server.GetTableInfo(tblName.c_str());
    if (!tableInfo) return;
    tableInfo->Print();
    delete tableInfo;
}

int vtbl::fill(TSQLStatement *statement, int verbose)
{
    if (!statement)
    {
        std::cerr << tblName << "::fill: statement invalid" << std::endl;
        return -1;
    }
    statement->Process();
    statement->StoreResult();
    if (statement->GetNumFields() != nFields)
    {
        std::cerr << tblName << "::fill: statement NumFields (" <<
            statement->GetNumFields() << ") != " << nFields << std::endl;
        return 0;
    }

    if (verbose)
    {
        std::cout << "NumFields = " << statement->GetNumFields() << std::endl;
        for (int i = 0; i < statement->GetNumFields(); i++)
            std::cout << "Field " << i << " = " << statement->GetFieldName(i) <<
            std::endl;
    }
    
    int nbytes = 0;
    while (statement->NextResultRow())
    {
        entry++;
        fillTblFields(statement, verbose);
        if (tree) nbytes += tree->Fill();
    }

    return nbytes;
}

int vtbl::fillByRun(int runID)
{
    std::ostringstream os;
    os << "SELECT * FROM " << tblName << " WHERE run_id=" << runID;
    std::string query(os.str().c_str());
    TMySQLStatement *result =
        (TMySQLStatement*)vtbl::server.Statement(os.str().c_str());

    int k = fill(result);
    delete result;
    return k;
}

void vtbl::getRunTimes(int runID,
    TTimeStamp &db_start_time, TTimeStamp &db_end_time) const
{
    db_start_time = 0;
    db_end_time = 0;

    std::ostringstream os;
    os << "SELECT db_start_time,db_end_time FROM tblRun_Info WHERE "
        "run_id=" << runID;
    TMySQLStatement *result =
        (TMySQLStatement*)vtbl::server.Statement(os.str().c_str());
    result->Process();
    result->StoreResult();

    if (result->NextResultRow())
    {
	int year, month, day, hour, min, sec, frac;
        result->GetTimestamp(0, year, month, day, hour, min, sec, frac);
        db_start_time = TTimeStamp(year, month, day, hour, min, sec);

        result->GetTimestamp(1, year, month, day, hour, min, sec, frac);
        db_end_time = TTimeStamp(year, month, day, hour, min, sec);
    }
    
    delete result;
}


TTimeStamp vtbl::xformIntToTimestamp(long timestamp) const
{
    // int value must look like YYYYMMDDHHMMSSXXX where XXX is some
    // fraction of seconds. because XXX length is not being assumed, the
    // safest way to do this is to convert to string, then pick off
    // values from the left.
    std::ostringstream os;
    os << timestamp;

    std::string t(os.str());
    // format the string to length we require.
    t = t.substr(0, 23);
    // total length needs to be 23 to accomodate nanosec properly in
    // this format.
    t.append(23 - t.length(), '0'); 

    int year = std::stoi(t.substr(0, 4));
    int month = std::stoi(t.substr(4, 2));
    int day = std::stoi(t.substr(6, 2));
    int hour = std::stoi(t.substr(8, 2));
    int minute = std::stoi(t.substr(10, 2));
    int second = std::stoi(t.substr(12, 2));
    int nsec = std::stoi(t.substr(14));
    //std::cout << year << " " << month << " " << day << " " << hour << " " <<
    //    minute << " " << second << " " << nsec << std::endl;
    return TTimeStamp(year, month, day, hour, minute, second, nsec);
}
