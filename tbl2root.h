#ifndef TBL2ROOT_H
#define TBL2ROOT_H

#include <string>

#include "TList.h"
#include "TMySQLServer.h"
#include "TMySQLStatement.h"
#include "TTree.h"

#include "tblL3_Telescope_TriggerInfo.h"
#include "tblRun_Info.h"

// create a TTree for tables in VERITAS database
class tbl2root
{
    public:
        tbl2root();
        virtual ~tbl2root();

	vtbl *addTbl(const char *tblName, TTree * &tree);
	const vtbl *getTbl(const char *tblName);
	const TTree *getTree(const char *treeName);
        int fillTree(const char *treeName = 0);
	void printTblList() const { if (tblList) tblList->Print(); }
        
        int queryByRun(const char *tblName, int runNum);

	void getL3RunStartStopTimes(int runID,
            double &runStart, double &runStop);

    private:
        static const std::string dbServer;
        static const std::string dbName;
        static const std::string dbUser;
        static const std::string dbPW;

        TMySQLServer *db;

	TList *tblList;
        TList *treeList;

        std::string genQuery();

};

#endif
