#include <iostream>
#include <stdexcept>
#include <sstream>

#include "TCollection.h"

#include "tbl2root.h"
#include "vtblFactory.h"

tbl2root::tbl2root()
{
    tblList = new TList();
}

tbl2root::~tbl2root()
{
    delete tblList;
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
