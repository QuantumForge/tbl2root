#include <iostream>

#include "tblRun_Info.h"
ClassImp(tblRun_Info);

tblRun_Info::tblRun_Info(): vtbl("tblRun_Info")
{
    Clear();
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


int tblRun_Info::Fill(TSQLStatement *statement, int verbose)
{
    if (!statement)
    {
        std::cerr << tblName << "::Fill: statement invalid" << std::endl;
        return -1;
    }
    statement->Process();
    statement->StoreResult();
    if (statement->GetNumFields() != nFields)
    {
        std::cerr << tblName << "::Fill: statement NumFields (" <<
            statement->GetNumFields() << ") != " << nFields << std::endl;
    }

    if (verbose)
    {
        std::cout << "NumFields = " << statement->GetNumFields() << std::endl;
        for (int i = 0; i < statement->GetNumFields(); i++)
            std::cout << "Field " << i << " = " << statement->GetFieldName(i) <<
            std::endl;
    }

    if (!statement->NextResultRow())
        return 0;

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

    Dump();
    std::cout << db_start_time.AsString() << std::endl;
    std::cout << db_end_time.AsString() << std::endl;
    std::cout << data_start_time.AsString() << std::endl;
    std::cout << data_end_time.AsString() << std::endl;
    
    return 1;
}
