#include "vtblFactory.h"

vtbl *vtblFactory::create(std::string tblName)
{
    if (tblName == "tblL3_Telescope_TriggerInfo")
    {
        return new tblL3_Telescope_TriggerInfo;
    }
    else if (tblName == "tblRun_Info")
    {
        return new tblRun_Info;
    }
    else
        return 0;
}
