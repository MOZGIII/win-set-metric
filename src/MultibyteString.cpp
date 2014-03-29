#include "MultibyteString.h"

#include <windows.h>

MultibyteString::MultibyteString(const wchar_t * string)
{
    int sizereq = WideCharToMultiByte(CP_UTF8, 0, string, -1, NULL, 0, NULL, NULL) + 2;
    buffer = new char[sizereq];
    memset(buffer, 0, sizereq);
    WideCharToMultiByte(CP_UTF8, 0, string, -1, buffer, sizereq, NULL, NULL);   
}

MultibyteString::~MultibyteString(void)
{
    delete[] buffer;
}

const char * MultibyteString::str(void) const
{
	return buffer;
}

MultibyteString::operator const char * ()
{
	return str();
}

