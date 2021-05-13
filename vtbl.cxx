#include <algorithm>
#include <stdexcept>

#include "vtbl.h"
ClassImp(vtbl);

// struct which defines what tables can be handled.
const std::vector<struct VTBLS> vtbl::vtbls = {
    {"tblL3_Telescope_TriggerInfo", "tblL3_Telescope_TriggerInfo", 12},
    {"tblRun_Info", "tblRun_Info", 20}
};

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
}
