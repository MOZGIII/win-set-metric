#pragma once

class MultibyteString
{
private:
    char * buffer;

public:
	MultibyteString(const wchar_t * string);
	~MultibyteString(void);

	const char * str(void) const;
	operator const char * ();
};
