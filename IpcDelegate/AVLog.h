#pragma once

class AVLog
{
public:
	AVLog();
	~AVLog();

	struct Options
	{
		bool use_thread = true;
		bool use_file_and_line = true;
	};

	virtual void TimeStamp(uint64_t* tik, uint64_t* freq) = 0;
	virtual uint32_t MessageNumber() = 0;
	virtual size_t ThreadId() = 0;
	virtual void WriteMessage(const char* msg, size_t msg_char_count) = 0;
	virtual const Options& GetOptions() = 0;

	static AVLog* ActiveLogInstance();

private:

	static AVLog* s_instance;
};

