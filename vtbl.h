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
        // vtbls must be updated when a new table is added.
	static const std::vector<struct VTBLS> vtbls; //! no streamer
        static TMySQLServer server;  //! no streamer

	std::string tblName;  //! no streamer
	std::string treeName; //! no streamer
	int nFields;          //! no streamer

	unsigned long entry;  // entry/event number counter

	TTree *tree;  //! no streamer

	//virtual std::string getRunTimesClause(TTimeStamp startTime,
        //    TTimeStamp stopTime) const = 0;
	virtual void fillTblFields(TSQLStatement *statement,
            int verbose = 0) = 0;
        virtual TTimeStamp xformIntToTimestamp(long timestamp) const;

    public:
        vtbl(std::string tblName_ = "");
        virtual ~vtbl(); 
	
	virtual void Clear(Option_t * = "") = 0;
        virtual void describe() const;
	virtual int fill(TSQLStatement *statement, int verbose = 0);
        virtual std::string getTblName() const { return tblName; }
	virtual int getNFields() const { return nFields; }
        virtual bool pingServer() const { return vtbl::server.PingVerify(); }

        virtual int fillByRun(int runID);
	//virtual int queryByStatement(TSQLServer *server, std::string stmt);
	virtual void getRunTimes(int runID, TTimeStamp &db_start_time,
            TTimeStamp &db_end_time) const;

        virtual unsigned long get_entry() const { return entry; }
        virtual void set_entry(unsigned long entry_) { entry = entry_; }

	virtual TTree *getTree() const { return tree; }
	virtual void setTree(TTree *tree_) { tree = tree_; }

	ClassDef(vtbl, 1);
};

#endif
