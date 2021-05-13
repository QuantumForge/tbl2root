#include <iostream>
#include "tblL3_Telescope_TriggerInfo.h"
ClassImp(tblL3_Telescope_TriggerInfo);


tblL3_Telescope_TriggerInfo::tblL3_Telescope_TriggerInfo():
    vtbl("tblL3_Telescope_TriggerInfo")
{
    Clear();
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

int tblL3_Telescope_TriggerInfo::Fill(TSQLStatement *statement, int verbose)
{
    if (!statement)
    {
        std::cerr << "tblL3_Telescope_TriggerInfo::Fill: statement invalid" <<
	    std::endl;
        return -1;
    }

    if (statement->GetNumFields() != nFields)
    {
        std::cerr << "tblL3_Telescope_TriggerInfo::Fill: "
	    "statement NumFields (" << statement->GetNumFields() <<
	    ") != " << nFields << std::endl;
        return -1;
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
    statement->GetTimestamp(0, timestamp);
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

   return 1;
}
