#ifndef VTBLFACTORY_H
#define VTBLFACTORY_H

#include <string>

#include "vtbl.h"
#include "tblL3_Array_TriggerInfo.h"
#include "tblL3_Telescope_TriggerInfo.h"
#include "tblRun_Info.h"
#include "tblWeather_Status.h"

class vtblFactory
{
    public:
        static vtbl *create(std::string tblName);
};

#endif
