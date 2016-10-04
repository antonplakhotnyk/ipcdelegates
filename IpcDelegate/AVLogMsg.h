#pragma once

static const size_t AV_LOG_MSG_CHARCOUNT = 1024*4;

class AVLogMsg
{
public:

	AVLogMsg(const char* file_name, int line, const char* function_name);
	void operator()(const char* format_msg, ...) const;

private:
	const char *const	m_file_name;
	const char *const	m_function_name;
	const int			m_line;
};

