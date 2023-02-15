#include "pch.h"
#include "ConsoleLog.h"
#include <ctime>

const WCHAR* GetDayW(int32 wday)
{
	switch (wday)
	{
	case 0:
		return L"Sun";
	case 1:
		return L"Mon";
	case 2:
		return L"Tue";
	case 3:
		return L"Wen";
	case 4:
		return L"Thu";
	case 5:
		return L"Fri";
	case 6:
		return L"Sat";
	default:
		return L"NUL";
	}
}

const WCHAR* GetMonthW(int32 wmonth)
{
	switch (wmonth)
	{
	case 0:
		return L"Jan";
	case 1:
		return L"Feb";
	case 2:
		return L"Mar";
	case 3:
		return L"Apr";
	case 4:
		return L"May";
	case 5:
		return L"Jun";
	case 6:
		return L"Jul";
	case 7:
		return L"Aug";
	case 8:
		return L"Sep";
	case 9:
		return L"Oct";
	case 10:
		return L"Nov";
	case 11:
		return L"Dec";
	default:
		return L"NUL";
	}
}


ConsoleLog::ConsoleLog()
{
	_stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	_stdErr = GetStdHandle(STD_ERROR_HANDLE);
}

ConsoleLog::~ConsoleLog()
{
}

void ConsoleLog::WriteStdOut(Color color, const WCHAR* format, ...)
{
	if (format == nullptr)
		return;

	SetColor(true, color);

	va_list ap;
	va_start(ap, format);
	vwprintf(format, ap);
	va_end(ap);

	fflush(stdout);

	SetColor(true, Color::WHITE);
}

void ConsoleLog::WriteStdErr(Color color, const WCHAR* format, ...)
{
	WCHAR buffer[BUFFER_SIZE];

	if (format == nullptr)
		return;

	SetColor(false, color);

	va_list ap;
	va_start(ap, format);
	vswprintf_s(buffer, BUFFER_SIZE, format, ap);
	va_end(ap);

	fwprintf_s(stderr, buffer);
	fflush(stderr);

	SetColor(false, Color::WHITE);
}

void ConsoleLog::WriteStdOutWithTime(Color color, const WCHAR* format, ...)
{
	if (format == nullptr)
		return;

	{
		time_t timer = time(nullptr);
		tm t;
		errno_t error;

		error = localtime_s(&t, &timer);
		if (error == 0)
			WriteStdOut(color, L"[%ws %ws %02d %02d:%02d:%02d %4d] ", GetDayW(t.tm_wday), GetMonthW(t.tm_mon),
			            t.tm_mday,
			            t.tm_hour,
			            t.tm_min,
			            t.tm_sec,
			            t.tm_year + 1900);
	}

	SetColor(true, color);
	wstring nowDate;
	va_list ap;
	va_start(ap, format);
	vwprintf(format, ap);
	va_end(ap);

	fflush(stdout);

	SetColor(true, Color::WHITE);
}

void ConsoleLog::SetColor(bool stdOut, Color color)
{
	static WORD SColors[]
	{
		0,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		FOREGROUND_RED | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
	};

	SetConsoleTextAttribute(stdOut ? _stdOut : _stdErr, SColors[static_cast<int32>(color)]);
}
