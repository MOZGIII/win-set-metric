#pragma once

#include "windows-api-headers.h"

class IfTable2Wrapper
{
private:
    PMIB_IF_TABLE2 table;

public:
    IfTable2Wrapper();
    ~IfTable2Wrapper();
    
	const ULONG NumEntries(void) const;
	MIB_IF_ROW2 & operator[] (int index);
};
