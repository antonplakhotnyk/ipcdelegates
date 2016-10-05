#include "stdafx.h"
#include "AVTimer.h"
#include <mach/clock.h>
#include <mach/mach.h>
#include "TimeConversion.h"

class InitClock
{
public:
    
    InitClock()
    {
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    }
  
    ~InitClock()
    {
        mach_port_deallocate(mach_task_self(), cclock);
    }
    
    clock_serv_t cclock;


} static s_clock;

uint64_t AVTimer::GetRawTik()
{
    mach_timespec_t ts;
    clock_get_time(s_clock.cclock, &ts);
	return ts.tv_sec*NANO_SCALE + ts.tv_nsec;
}

uint64_t AVTimer::GetRawTikFrequency()
{
    return NANO_SCALE;
}
