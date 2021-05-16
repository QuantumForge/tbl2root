#ifndef VTBL_H
#define VTBL_H

#include <string>

#include "TObject.h"
#include "TSQLStatement.h"
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
	static const std::vector<struct VTBLS> vtbls;

	std::string tblName;
	std::string treeName;
	int nFields;

	TTree *tree;

	virtual void fillTblFields(TSQLStatement *statement,
            int verbose = 0) = 0;

    public:
        vtbl(std::string tblName_ = "");
        virtual ~vtbl(); 

	virtual void Clear(Option_t * = "") = 0;
	virtual int fill(TSQLStatement *statement, int verbose = 0);
        virtual std::string getTblName() const { return tblName; }
	virtual int getNFields() const { return nFields; }

	virtual TTree *getTree() const { return tree; }
	virtual void setTree(TTree *tree_) { tree = tree_; }

	ClassDef(vtbl, 1);
};

#endif
