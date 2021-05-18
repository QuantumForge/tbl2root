#include <iostream>

#include "tblRun_Info.h"
ClassImp(tblRun_Info);

tblRun_Info::tblRun_Info(): vtbl("tblRun_Info")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch("run_id", &(this->run_id));
    tree->Branch("run_type", &(this->run_type));
    tree->Branch("observing_mode", &(this->observing_mode));
    tree->Branch("run_status", &(this->run_status));
    tree->Branch("db_start_time", &(this->db_start_time));
    tree->Branch("db_end_time", &(this->db_end_time));
    tree->Branch("data_start_time", &(this->data_start_time));
    tree->Branch("data_end_time", &(this->data_end_time));
    tree->Branch("duration", &(this->duration));
    tree->Branch("weather", &(this->weather));
    tree->Branch("config_mask", &(this->config_mask));
    tree->Branch("pointing_mode", &(this->pointing_mode));
    tree->Branch("trigger_config", &(this->trigger_config));
    tree->Branch("trigger_multiplicity", &(this->trigger_multiplicity));
    tree->Branch("trigger_coincidence", &(this->trigger_coincidence));
    tree->Branch("offsetRA", &(this->offsetRA));
    tree->Branch("offsetDEC", &(this->offsetDEC));
    tree->Branch("offset_distance", &(this->offset_distance));
    tree->Branch("offset_angle", &(this->offset_angle));
    tree->Branch("source_id", &(this->source_id));
}

tblRun_Info::~tblRun_Info()
{

}

void tblRun_Info::Clear(Option_t *option)
{
    run_id = 0;
    run_type = 0;
    observing_mode = 0;
    run_status = 0;
    db_start_time = 0;
    db_end_time = 0;
    data_start_time = 0;
    data_end_time = 0;
    duration = 0;
    weather = 0;
    config_mask = 0;
    pointing_mode = 0;
    trigger_config = 0;
    trigger_multiplicity = 0;
    trigger_coincidence = 0;
    offsetRA = 0;
    offsetDEC = 0;
    offset_distance = 0;
    offset_angle = 0;
    source_id = "";
}


void tblRun_Info::fillTblFields(TSQLStatement *statement, int verbose)
{
    run_id = statement->GetInt(0);
    run_type = statement->GetInt(1);
    observing_mode = statement->GetInt(2);
    run_status = statement->GetInt(3);
    int year, month, day, hour, min, sec, frac;
    statement->GetTimestamp(4, year, month, day, hour, min, sec, frac);
    db_start_time = TTimeStamp(year, month, day, hour, min, sec);
    statement->GetTimestamp(5, year, month, day, hour, min, sec, frac);
    db_end_time = TTimeStamp(year, month, day, hour, min, sec);
    statement->GetTimestamp(6, year, month, day, hour, min, sec, frac);
    data_start_time = TTimeStamp(year, month, day, hour, min, sec);
    statement->GetTimestamp(7, year, month, day, hour, min, sec, frac);
    data_end_time = TTimeStamp(year, month, day, hour, min, sec);
    duration = statement->GetUInt(8);
    weather = statement->GetInt(9);
    config_mask = statement->GetUInt(10);
    pointing_mode = statement->GetInt(11);
    trigger_config = statement->GetInt(12);
    trigger_multiplicity = statement->GetUInt(13);
    trigger_coincidence = statement->GetDouble(14);
    offsetRA = statement->GetDouble(15);
    offsetDEC = statement->GetDouble(16);
    offset_distance = statement->GetDouble(17);
    offset_angle = statement->GetDouble(18);
    source_id = statement->GetString(19);
}
