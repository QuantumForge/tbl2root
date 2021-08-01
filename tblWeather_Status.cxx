#include <iomanip>
#include <iostream>
#include <sstream>

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

int tblWeather_Status::fillByDate(const char *yyyymmdd)
{
    std::string date(yyyymmdd);
    int year  = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(4, 2));
    int day   = std::stoi(date.substr(6, 2));

    return fillByDate(year, month, day);
}


int tblWeather_Status::fillByDate(int year, int month, int day)
{
    std::ostringstream os;
    os << std::setw(4) << std::setfill('0') << year << "-" << std::setw(2) <<
        month << "-" << std::setw(2) << day << " 00:00:00";
    std::string start_time = os.str();
    os.str("");
    os << std::setw(4) << std::setfill('0') << year << "-" << std::setw(2) <<
        month << "-" << std::setw(2) << day << " 23:59:59";
    std::string stop_time = os.str();
  
    os.str(""); 
    os << "SELECT * FROM " << tblName << " WHERE " <<
        "timestamp >= '" << start_time << "' AND timestamp <= '" <<
        stop_time << "'";
    std::string query(os.str().c_str());
    std:: cout << "query: " << query << std::endl;
    TMySQLStatement *result =
        (TMySQLStatement*)vtbl::server.Statement(query.c_str());

    int k = fill(result);
    delete result;
    return k;



}
