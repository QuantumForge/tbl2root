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
    treeList = new TList();
}

tbl2root::~tbl2root()
{
    delete treeList;
    delete tblList;
    db->Close();
    delete db;
}

vtbl *tbl2root::addTbl(const char *tblName, TTree * &tree)
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
    TTree *t1 = new TTree(newTbl->getTblName().c_str(),
        newTbl->getTblName().c_str());
    t1->Branch(newTbl->getTblName().c_str(), newTbl);
    treeList->Add(t1);
    tree = t1;
    return newTbl;
}

const vtbl *tbl2root::getTbl(const char *tblName)
{
    return (const vtbl*)tblList->FindObject(tblName);
}

const TTree *tbl2root::getTree(const char *treeName)
{
    return (const TTree*)treeList->FindObject(treeName);
}

int tbl2root::fillTree(const char *treeName)
{
    int nbytes = 0;
    TIter next(treeList);
    while (TTree *t = (TTree*)next())
    {
        if (!treeName || std::string(t->GetName()) == treeName)
            nbytes += t->Fill();
    }
    return nbytes;
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
