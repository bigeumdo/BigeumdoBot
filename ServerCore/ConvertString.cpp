#include "pch.h"
#include "ConvertString.h"

WCHAR* ConvertS2W(const string& v)
{
	auto orig = v.c_str();

	auto wcstring = new WCHAR[BUFFER_MAX];

	size_t convertedChars = 0;
	errno_t error;
	error = mbstowcs_s(&convertedChars, wcstring, BUFFER_MAX, orig, _TRUNCATE);

	if (error != 0)
	{
		CRASH(error);
	}

	return wcstring;
}

WCHAR* ConvertS2W(const char* v)
{
	auto wcstring = new WCHAR[BUFFER_MAX];

	size_t convertedChars = 0;
	errno_t error;
	error = mbstowcs_s(&convertedChars, wcstring, BUFFER_MAX, v, _TRUNCATE);

	if (error != 0)
	{
		CRASH(error);
	}

	return wcstring;
}

char* ConvertW2MBS(const WCHAR* v)
{
	auto string = new char[BUFFER_MAX];

	size_t convertedChars = 0;
	errno_t error;
	error = wcstombs_s(&convertedChars, string, BUFFER_MAX, v, _TRUNCATE);
	if (error != 0)
	{
		CRASH(error);
	}

	return string;
}
