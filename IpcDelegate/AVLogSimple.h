#pragma once

#include "AVLog.h"

class AVLogSimple: public AVLog
{
public:
	AVLogSimple();
	~AVLogSimple();

private:

	void TimeStamp(uint64_t* tik, uint64_t* freq) final;
	size_t ThreadId() override;
	uint32_t MessageNumber() final;
	void WriteMessage(const char* msg, size_t msg_char_count) final;
	const AVLog::Options& GetOptions() final;

	virtual void SendLog(const char* msg, int msg_char_count) = 0;

protected:
	Options		m_options;
private:
	uint32_t	m_message_number;
	uint64_t	m_start;
};

