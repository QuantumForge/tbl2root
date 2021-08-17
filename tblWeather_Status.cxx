#include "TMySQLStatement.h"

#include "tblWeather_Status.h"
ClassImp(tblWeather_Status);

tblWeather_Status::tblWeather_Status(): vtbl("tblWeather_Status")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch(tblName.c_str(), this);
}

tblWeather_Status::~tblWeather_Status()
{

}

void tblWeather_Status::Clear(Option_t *option)
{
    timestamp = 0;
    Batt_Volt = 0;
    WS_mph_Avg = 0;
    WS_mph_Max = 0;
    WS_mph_Min = 0;
    WindDir = 0;
    AirTF_Avg = 0;
    RH = 0;
    Rain_in_Tot = 0;
    SlrW_Avg = 0;
    SlrkJ_Tot = 0;
    BP_mbar_Avg = 0;
}


void tblWeather_Status::fillTblFields(TSQLStatement *statement, int verbose)
{
    int year, month, day, hour, min, sec, frac;
    statement->GetTimestamp(0, year, month, day, hour, min, sec, frac);
    timestamp = TTimeStamp(year, month, day, hour, min, sec);
    Batt_Volt = statement->GetDouble(1);
    WS_mph_Avg = statement->GetDouble(2);
    WS_mph_Max = statement->GetDouble(3);
    WS_mph_Min = statement->GetDouble(4);
    WindDir = statement->GetDouble(5);
    AirTF_Avg = statement->GetDouble(6);
    RH = statement->GetDouble(7);
    Rain_in_Tot = statement->GetDouble(8);
    SlrW_Avg = statement->GetDouble(9);
    SlrkJ_Tot = statement->GetDouble(10);
    BP_mbar_Avg = statement->GetDouble(11);
}


