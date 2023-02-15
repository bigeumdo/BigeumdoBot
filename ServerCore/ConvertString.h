#pragma once

#define BUFFER_MAX 1024

WCHAR* ConvertS2W(const string& v);

WCHAR* ConvertS2W(const char* v);

char* ConvertW2MBS(const WCHAR* v);
