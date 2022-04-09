#include "TMySQLStatement.h"

#include "tblFIR_Pyrometer_Info.h"
ClassImp(tblFIR_Pyrometer_Info);

tblFIR_Pyrometer_Info::tblFIR_Pyrometer_Info(): vtbl("tblFIR_Pyrometer_Info")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch(tblName.c_str(), this);
}

tblFIR_Pyrometer_Info::~tblFIR_Pyrometer_Info()
{

}

void tblFIR_Pyrometer_Info::Clear(Option_t *option)
{
    timestamp = 0;
    telescope_id = 0;
    ambient_temp = 0.;
    radiant_sky_temp = 0.;
}


void tblFIR_Pyrometer_Info::fillTblFields(TSQLStatement *statement, int verbose)
{
    int year, month, day, hour, min, sec, frac;
    statement->GetTimestamp(0, year, month, day, hour, min, sec, frac);
    timestamp = TTimeStamp(year, month, day, hour, min, sec);
    telescope_id = static_cast<unsigned short>(statement->GetUInt(1));
    ambient_temp = statement->GetDouble(2);
    radiant_sky_temp = statement->GetDouble(3);
}
