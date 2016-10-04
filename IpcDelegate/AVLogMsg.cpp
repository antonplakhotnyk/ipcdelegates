#include "stdafx.h"
#include "AVLogMsg.h"
#include "AVLogMsgFormat.h"

AVLogMsg::AVLogMsg(const char* file_name, int line, const char* function_name)
	:m_file_name(file_name)
	, m_line(line)
	, m_function_name(function_name)
{
}

void AVLogMsg::operator()(const char* format_msg, ...) const
{
	AVLog* log = AVLog::ActiveLogInstance();
	if( log )
	{
		va_list		arg_list;
		va_start(arg_list, format_msg);

		AVLogMsgFormat(log, m_file_name, m_line, m_function_name, format_msg, arg_list);

		va_end(arg_list);
	}
}

