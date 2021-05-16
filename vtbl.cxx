#include <algorithm>
#include <iostream>
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

    tree = new TTree(tblName.c_str(), tblName.c_str());
    tree->Branch(tblName.c_str(), this);
}

vtbl::~vtbl()
{
    delete tree;
}

int vtbl::fill(TSQLStatement *statement, int verbose)
{
    if (!statement)
    {
        std::cerr << tblName << "::fill: statement invalid" << std::endl;
        return -1;
    }
    statement->Process();
    statement->StoreResult();
    if (statement->GetNumFields() != nFields)
    {
        std::cerr << tblName << "::fill: statement NumFields (" <<
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

    fillTblFields(statement, verbose);

    if (tree)
        tree->Fill();

    return 1;
}
