#include "stdafx.h"
#include "AVPlatformSpecific.h"
#include <pthread.h>


size_t AVGetCurrentThreadId()
{
    mach_port_t machTID = pthread_mach_thread_np(pthread_self());
	return machTID;
}
