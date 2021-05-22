#include <iostream>
#include <sstream>

#include "TMySQLStatement.h"

#include "tblL3_Telescope_TriggerInfo.h"
ClassImp(tblL3_Telescope_TriggerInfo);


tblL3_Telescope_TriggerInfo::tblL3_Telescope_TriggerInfo():
    vtbl("tblL3_Telescope_TriggerInfo")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch(tblName.c_str(), this);
}

tblL3_Telescope_TriggerInfo::~tblL3_Telescope_TriggerInfo()
{

}

void tblL3_Telescope_TriggerInfo::Clear(Option_t *option)
{
    timestamp = 0;
    run_id = 0;
    telescope_id = 0;
    L2 = 0;
    QI = 0;
    HM = 0;
    NP = 0;
    L2LL3 = 0;
    L3 = 0;
    VDAQBusy = 0.;
    VDAQBusyScaler = 0;
    TenMHzScaler = 0;
}

void tblL3_Telescope_TriggerInfo::fillTblFields(TSQLStatement *statement,
    int verbose)
{
    long int t = statement->GetLong(0);
    timestamp = xformIntToTimestamp(t);
    run_id = statement->GetInt(1);
    telescope_id = statement->GetUInt(2);
    L2 = statement->GetInt(3);
    QI = statement->GetInt(4);
    HM = statement->GetInt(5);
    NP = statement->GetInt(6);
    L2LL3 = statement->GetInt(7);
    L3 = statement->GetInt(8);
    VDAQBusy = statement->GetDouble(9);
    VDAQBusyScaler = statement->GetUInt(10);
    TenMHzScaler = statement->GetUInt(11);
}

int tblL3_Telescope_TriggerInfo::fillByRun(int runID)
{
    TTimeStamp start, stop;
    getRunTimes(runID, start, stop);

    if (start.AsDouble() <= 1.e-9 || stop.AsDouble() <= 1.e-9)
    {
        std::cerr << "tblL3_Telescope_TriggerInfo::fillByRun: start: " <<
            start.AsString() << ", stop: " << stop.AsString() << std::endl;
        return 0;
    }

    std::ostringstream start_timestamp;
    start_timestamp << start.GetDate() << start.GetTime() << "000";
    std::ostringstream stop_timestamp;
    stop_timestamp << stop.GetDate() << stop.GetTime() << "000";

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
