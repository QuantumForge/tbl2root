#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "TMySQLStatement.h"

#include "vtbl.h"
ClassImp(vtbl);

// struct which defines what tables can be handled.
const std::vector<struct VTBLS> vtbl::vtbls = {
    {"tblL3_Telescope_TriggerInfo", "tblL3_Telescope_TriggerInfo", 12},
    {"tblRun_Info", "tblRun_Info", 20}
};

TMySQLServer vtbl::server("mysql://romulus.ucsc.edu/VERITAS",
    "readonly", "");

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

    //std::cout << vtbl::server.ServerInfo() << std::endl;
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
        return 0;
    }

    if (verbose)
    {
        std::cout << "NumFields = " << statement->GetNumFields() << std::endl;
        for (int i = 0; i < statement->GetNumFields(); i++)
            std::cout << "Field " << i << " = " << statement->GetFieldName(i) <<
            std::endl;
    }
    
    int nbytes = 0;
    while (statement->NextResultRow())
    {
        std::cout << "nbytes" << std::endl;
        fillTblFields(statement, verbose);
        if (tree) nbytes += tree->Fill();
    }

    return nbytes;
}

int vtbl::fillByRun(int runID)
{
    std::ostringstream os;
    os << "SELECT * FROM " << tblName << " WHERE run_id=" << runID;
    std::string query(os.str().c_str());
    TMySQLStatement *result =
        (TMySQLStatement*)vtbl::server.Statement(os.str().c_str());

    int k = fill(result);
    return k;
}
