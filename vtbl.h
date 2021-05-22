#ifndef VTBL_H
#define VTBL_H

#include <string>

#include "TMySQLServer.h"
#include "TObject.h"
#include "TSQLStatement.h"
#include "TTimeStamp.h"
#include "TTree.h"

struct VTBLS
{
    std::string tblName;
    std::string treeName;
    unsigned int nFields;
};

class vtbl: public TObject
{
    protected:
	static const std::vector<struct VTBLS> vtbls; //! no streamer
        static TMySQLServer server;  //! no streamer

	std::string tblName;
	std::string treeName;
	int nFields;

	TTree *tree;  //! no streamer

	virtual void fillTblFields(TSQLStatement *statement,
            int verbose = 0) = 0;

    public:
        vtbl(std::string tblName_ = "");
        virtual ~vtbl(); 
	
	virtual void Clear(Option_t * = "") = 0;
        virtual void describe() const;
	virtual int fill(TSQLStatement *statement, int verbose = 0);
        virtual std::string getTblName() const { return tblName; }
	virtual int getNFields() const { return nFields; }

        virtual int fillByRun(int runID);
	//virtual int queryByStatement(TSQLServer *server, std::string stmt);
	virtual void getRunTimes(int runID, TTimeStamp &db_start_time,
            TTimeStamp &db_end_time) const;

	virtual TTree *getTree() const { return tree; }
	virtual void setTree(TTree *tree_) { tree = tree_; }

	ClassDef(vtbl, 1);
};

#endif
