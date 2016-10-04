#include "stdafx.h"
#include "AVPlatformSpecific.h"
#include <Windows.h>


size_t AVGetCurrentThreadId()
{
	return GetCurrentThreadId();
}
