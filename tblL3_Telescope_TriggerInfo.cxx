#include <iostream>
#include "tblL3_Telescope_TriggerInfo.h"
ClassImp(tblL3_Telescope_TriggerInfo);


tblL3_Telescope_TriggerInfo::tblL3_Telescope_TriggerInfo():
    vtbl("tblL3_Telescope_TriggerInfo")
{
    Clear();
    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch("timestamp", &(this->timestamp));
    tree->Branch("run_id", &(this->run_id));
    tree->Branch("telescope_id", &(this->telescope_id));
    tree->Branch("L2", &(this->L2));
    tree->Branch("QI", &(this->QI));
    tree->Branch("HM", &(this->HM));
    tree->Branch("NP", &(this->NP));
    tree->Branch("L2LL3", &(this->L2LL3));
    tree->Branch("L3", &(this->L3));
    tree->Branch("VDAQBusy", &(this->VDAQBusy));
    tree->Branch("VDAQBusyScaler", &(this->VDAQBusyScaler));
    tree->Branch("TenMHzScaler", &(this->TenMHzScaler));
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
    int year, month, day, hour, min, sec, frac;
    statement->GetTimestamp(0, year, month, day, hour, min, sec, frac);
    timestamp = TTimeStamp(year, month, day, hour, min, sec);
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
