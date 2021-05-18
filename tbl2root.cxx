#include <iostream>
#include <stdexcept>
#include <sstream>

#include "TCollection.h"

#include "tbl2root.h"
#include "vtblFactory.h"

const std::string tbl2root::dbServer("mysql://romulus.ucsc.edu/VERITAS");
const std::string tbl2root::dbName("VERITAS");
const std::string tbl2root::dbUser("readonly");
const std::string tbl2root::dbPW("");

tbl2root::tbl2root()
{
    db = new TMySQLServer(tbl2root::dbServer.c_str(),
        tbl2root::dbUser.c_str(), tbl2root::dbPW.c_str());
    if (!db)
        throw std::runtime_error("tbl2root: CAN'T OPEN DATABASE");
    if (db->IsError())
	throw std::runtime_error(db->GetErrorMsg());

    tblList = new TList();
}

tbl2root::~tbl2root()
{
    delete tblList;
    db->Close();
    delete db;
}

vtbl *tbl2root::addTbl(const char *tblName)
{
    if (tblList->FindObject(tblName))
    {
        std::cerr << "tbl2root::addTbl: table already exists." << std::endl;
        return 0;
    }

    vtbl *newTbl = vtblFactory::create(tblName);
    if (!newTbl)
    {
        std::cerr << "tbl2root::addTbl: Failed to create table." << std::endl;
	return 0;
    }

    tblList->Add(newTbl);	
    return newTbl;
}

vtbl *tbl2root::getTbl(const char *tblName) const
{
    return (vtbl*)tblList->FindObject(tblName);
}

void tbl2root::getL3RunStartStopTimes(int runID, double &runStart,
    double &runStop)
{
    std::ostringstream os;
    os << "SELECT * FROM tblRun_Info WHERE run_id=" << runID;
    std::string query(os.str().c_str());
    TMySQLStatement *result = (TMySQLStatement*)db->Statement(os.str().c_str());

    tblRun_Info run_info;
    run_info.Fill(result, 1);

    std::cout << runStart << " " << runStop << std::endl;
    delete result;
}
