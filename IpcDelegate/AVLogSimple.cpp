#include "stdafx.h"
#include "AVLogSimple.h"
#include "AVTimer.h"
#include "AVPlatformSpecific.h"


AVLogSimple::AVLogSimple()
	:m_message_number(1)
{
	m_start = AVTimer::GetRawTik();
}

AVLogSimple::~AVLogSimple()
{
}

void AVLogSimple::TimeStamp(uint64_t* tik, uint64_t* freq)
{
	*tik = AVTimer::GetRawTik();
	*tik -= m_start;
	*freq = AVTimer::GetRawTikFrequency();
}

size_t AVLogSimple::ThreadId()
{
	return AVGetCurrentThreadId();
}

uint32_t AVLogSimple::MessageNumber()
{
	return m_message_number;
}

void AVLogSimple::WriteMessage(const char* msg, size_t msg_char_count)
{
	m_message_number++;
	SendLog(msg, msg_char_count);
}

const AVLog::Options& AVLogSimple::GetOptions()
{
	return m_options;
}
