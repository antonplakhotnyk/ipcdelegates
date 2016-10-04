#include "stdafx.h"
#include "Windows.h"
#include "AVTimer.h"


uint64_t AVTimer::GetRawTik()
{
	LARGE_INTEGER time;
	::QueryPerformanceCounter(&time);
	return time.QuadPart;
}

uint64_t AVTimer::GetRawTikFrequency()
{
	LARGE_INTEGER time;
	QueryPerformanceFrequency(&time);
	return time.QuadPart;
}
