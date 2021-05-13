#ifndef VTBL_H
#define VTBL_H

#include <string>

#include "TSQLStatement.h"
#include "TObject.h"

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

    public:
        vtbl(std::string tblName_ = "");

	virtual void Clear(Option_t * = "") = 0;
	virtual int Fill(TSQLStatement *statement, int verbose = 0) = 0;
        virtual std::string getTblName() const { return tblName; }
	virtual int getNFields() const { return nFields; }

	ClassDef(vtbl, 1);
};

#endif
