#pragma once

#include <cstdarg>
#include "AVLog.h"

void AVLogMsgFormat(AVLog* log, const char* src_file, int src_line, const char* function_name, const char* format, va_list ptr);
