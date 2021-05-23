#include <iomanip>
#include <iostream>
#include <sstream>

#include "TMySQLStatement.h"

#include "tblL3_Array_TriggerInfo.h"
ClassImp(tblL3_Array_TriggerInfo);


tblL3_Array_TriggerInfo::tblL3_Array_TriggerInfo():
    vtbl("tblL3_Array_TriggerInfo")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch(tblName.c_str(), this);
}

tblL3_Array_TriggerInfo::~tblL3_Array_TriggerInfo()
{

}

void tblL3_Array_TriggerInfo::Clear(Option_t *option)
{
    timestamp = 0;
    run_id = 0;
    L3 = 0;
    L3orVDAQBusy = 0.;
    VDAQBusy = 0.;
    SpareBusy = 0.;
    PED = 0;
    OC = 0;
    VDAQBusyScaler = 0;
    L3orVDAQBusyScaler = 0;
    TenMHzScaler = 0;
}

void tblL3_Array_TriggerInfo::fillTblFields(TSQLStatement *statement,
    int verbose)
{
    timestamp = xformIntToTimestamp(statement->GetLong(0));
    run_id = statement->GetInt(1);
    L3 = statement->GetInt(2);
    L3orVDAQBusy = statement->GetDouble(3);
    VDAQBusy = statement->GetDouble(4);
    SpareBusy = statement->GetDouble(5);
    PED = statement->GetUInt(6);
    OC = statement->GetUInt(7);
    VDAQBusyScaler = statement->GetUInt(8);
    L3orVDAQBusyScaler = statement->GetUInt(9);
    TenMHzScaler = statement->GetUInt(10);
}

int tblL3_Array_TriggerInfo::fillByRun(int runID)
{
    pingServer();
    TTimeStamp start, stop;
    getRunTimes(runID, start, stop);

    if (start.AsDouble() <= 1.e-9 || stop.AsDouble() <= 1.e-9)
    {
        std::cerr << "tblL3_Array_TriggerInfo::fillByRun: start: " <<
            start.AsString() << ", stop: " << stop.AsString() << std::endl;
        return 0;
    }

    // we pad the timestamps with 0s on the right because tblRun_Info timestamps
    // are different from L3 table timestamps
    std::ostringstream start_timestamp;
    start_timestamp << start.GetDate() << std::setfill('0') << std::setw(6) <<
        start.GetTime() << "000";
    std::ostringstream stop_timestamp;
    stop_timestamp << stop.GetDate() << std::setfill('0') << std::setw(6) <<
        stop.GetTime() << "000";

    std::ostringstream os;
    os << "SELECT * FROM " << tblName << " WHERE run_id=" << runID <<
        " AND timestamp>" << start_timestamp.str() <<
        " AND timestamp<" << stop_timestamp.str();
    std::string query(os.str().c_str());
    std:: cout << "query: " << query << std::endl;
    TMySQLStatement *result =
        (TMySQLStatement*)vtbl::server.Statement(query.c_str());

    int k = fill(result);
    delete result;
    return k;
}
