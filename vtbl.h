#ifndef VTBL_H
#define VTBL_H

#include <string>

#include "TMySQLServer.h"
#include "TObject.h"
#include "TSQLStatement.h"
#include "TTimeStamp.h"
#include "TTree.h"

// class which describes the tables that can be accomodated. when a new table
// is implemented, it needs to be defined in the base class instance of this
// class.
struct VTBLS
{
    std::string tblName;
    std::string treeName;
    unsigned int nFields;
};

// vtbl mimics the structure of VERITAS mysql tables storing the fields in a
// TTree (named tree in the class). Each table in the mysql database needs
// to inherit this base class and implement the fillTblFields method to copy
// the mysql field data into the derived class's members. The tree that is
// filled from queries generated by the user can be stored in a TFile by
// doing something like:
//
// TFile *f = new TFile("tbl.root", "RECREATE");
// tblX *x = new tblX();
// x->fillByRun(run_number);
// x->getTree()->Write();
// f->Close();
//
class vtbl: public TObject
{
    protected:
        // vtbls must be updated when a new table is added.
	static const std::vector<struct VTBLS> vtbls; //! no streamer
        static TMySQLServer server;  //! no streamer

	std::string tblName;  //! no streamer
	std::string treeName; //! no streamer
	int nFields;          //! no streamer

	unsigned long entry;  // entry/event number counter in the tree

	TTree *tree;  //! no streamer

	//virtual std::string getRunTimesClause(TTimeStamp startTime,
        //    TTimeStamp stopTime) const = 0;

        // each derived class must implement its own fillTblFields method.
        // fillTblFields uses the provided TSQLStatement to fill the 
        // class members data from the info read from the data base for
        // a single row. this method basically translates mysql data to
        // ROOT tree leaves.
	virtual void fillTblFields(TSQLStatement *statement,
            int verbose = 0) = 0;
        virtual TTimeStamp xformIntToTimestamp(long timestamp) const;

    public:
        vtbl(std::string tblName_ = "");
        virtual ~vtbl(); 
	
	virtual void Clear(Option_t * = "") = 0;
        virtual void describe() const;



        // use fill in a method to to get the
        // data into the ROOT tree. this should be used in a method like
        // fillByRun or fillByDate, where a selection clause is used to
        // pick events (e.g., get all events in tbl_L3_Array_TriggerInfo for
        // 20210614) and  creating a TMySQLStatement. that statement is
        // given to the fill method, which will loop over all rows in the
        // statement and run fillTblFields on each one to extract the data
        // into the class members (and ROOT tree).
	virtual int fill(TSQLStatement *statement, int verbose = 0);

        virtual std::string getTblName() const { return tblName; }
	virtual int getNFields() const { return nFields; }

        // call pingServer in your the beginning of your methods that
        // access the database and readout data with the fill method.
        virtual bool pingServer() const { return vtbl::server.PingVerify(); }

        // fills class members from the mysql table for a given run id.
        // fillByRun does not add a condition based on the start and stop times
        // of the run. some tables need that information to search the db
        // much more quickly, so they should implement their own version.
        // see for example tblL3_Array_TriggerInfo.cxx
        virtual int fillByRun(int runID);
	//virtual int queryByStatement(TSQLServer *server, std::string stmt);
        
        // fills class members from the mysql table for a given date
        // example in tblWeather_Status
        virtual int fillByDate(const char *yyyymmdd, bool verbose = false);
	virtual int fillByDate(int year, int month, int day,
                bool verbose = false);
        //int fillByDate(TTimeStamp *ts);



	// User provides a run id, and the start and stop times are searched
	// in the tblRun_Info table. Using start and and stop times when
	// querying data is faster than simply specifying run id.
	virtual void getRunTimes(int runID, TTimeStamp &db_start_time,
            TTimeStamp &db_end_time) const;

        // get the number of entries in the member tree
        virtual unsigned long get_entry() const { return entry; }
        virtual void set_entry(unsigned long entry_) { entry = entry_; }

	virtual TTree *getTree() const { return tree; }
	virtual void setTree(TTree *tree_) { tree = tree_; }

	ClassDef(vtbl, 1);
};

#endif
