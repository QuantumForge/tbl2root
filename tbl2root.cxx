#include <iostream>
#include <sstream>

#include "tbl2root.h"
ClassImp(tbl2root);

const std::string tbl2root::dbServer("mysql://romulus.ucsc.edu/VERITAS");
const std::string tbl2root::dbName("VERITAS");
const std::string tbl2root::dbUser("readonly");
const std::string tbl2root::dbPW("");

tbl2root::tbl2root()
{
    db = new TMySQLServer(tbl2root::dbServer.c_str(),
        tbl2root::dbUser.c_str(), tbl2root::dbPW.c_str());
    if (!db)
        std::cerr << "DB NOT OPENED" << std::endl;
}

tbl2root::~tbl2root()
{
    db->Close();
    delete db;
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
