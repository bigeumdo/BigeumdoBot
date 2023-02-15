#pragma once
#include <vector>
#include "Types.h"

/*-----------------
	FileUtils
------------------*/

class FileUtils
{
public:
	static vector<BYTE> ReadFile(const WCHAR* path);
	static wstring Convert(string str);
};
