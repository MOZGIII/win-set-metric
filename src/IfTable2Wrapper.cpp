#include "IfTable2Wrapper.h"

IfTable2Wrapper::IfTable2Wrapper() : 
    table(NULL)
{
    DWORD val = GetIfTable2Ex(MibIfTableRaw, &table);
    if (val != NO_ERROR)
    {
        throw("GetIfTable2Ex returned error: " + val);
    }
}

IfTable2Wrapper::~IfTable2Wrapper()
{
    if(table != NULL)
    {
        FreeMibTable(table);
    }
}

const ULONG IfTable2Wrapper::NumEntries(void) const
{
	return table->NumEntries;
}

MIB_IF_ROW2 & IfTable2Wrapper::operator[] (int index)
{
	return table->Table[index];
}
