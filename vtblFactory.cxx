#include "vtblFactory.h"

vtbl *vtblFactory::create(std::string tblName)
{
    if (tblName == "tblL3_Array_TriggerInfo")
    {
        return new tblL3_Array_TriggerInfo;
    }
    else if (tblName == "tblL3_Telescope_TriggerInfo")
    {
        return new tblL3_Telescope_TriggerInfo;
    }
    else if (tblName == "tblRun_Info")
    {
        return new tblRun_Info;
    }
    else if (tblName == "tblWeather_Status")
    {
        return new tblWeather_Status;
    }
    else
        return 0;
}
