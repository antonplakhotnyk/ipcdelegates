#include "stdafx.h"
#include "AVLogMsgFormat.h"



static uint64_t Mul12(int mul1, const uint64_t mul2)
{
	return mul1 * mul2;
}

static int Separate(uint64_t& tik, const uint64_t& freq)
{
	register int part = int(tik/freq);
	tik -= Mul12(part, freq);//tik -= part * freq;
	tik = Mul12(1000, tik);//tik *= 1000;
	return part;
}

static void FormatTime(uint64_t tik, uint64_t freq, int* sec, int* ms, int* mks, int* ns)
{
	*sec = Separate(tik, freq);
	*ms = Separate(tik, freq);
	*mks = Separate(tik, freq);
	*ns = Separate(tik, freq);

	// 	*sec = int(tik/freq);
	// 	tik -= (*sec) * freq;
	// 	tik *= 1000;
	// 
	// 	*ms = int(tik/freq);
	// 	tik -= (*ms) * freq;
	// 	tik *= 1000;
	// 
	// 	*mks = int(tik/freq);
	// 	tik -= (*mks) * freq;
	// 	tik *= 1000;
	// 
	// 	*ns = int(tik/freq);
}

void AVLogMsgFormat(AVLog* log, const char* src_file, int src_line, const char* function_name, const char* format, va_list ptr)
{
	// ≈сли сообщение не поместилось, не обрезать а писать в лог "—ообщение не поместилось"
// #pragma todo("bug")
// 	size_t len = 0;
// 	size_t res;
// 
// 	uint64_t	tik;
// 	uint64_t	freq;
// 	char		buffer[AV_LOG_MSG_CHARCOUNT];
// 	size_t		buffer_char_count_max = COUNTOF(buffer);
// 	size_t		printed_char_count_without_null;
// 	const AVLog::Options& options = log->GetOptions();
// 
// 	log->TimeStamp(&tik, &freq);
// 	auto message_number = log->MessageNumber();
// 
// 	if( ((src_file!=NULL) && (src_line!=0)) && options.use_file_and_line )
// 	{
// 		if( len >= 0 && len < buffer_char_count_max )
// 		{
// 			res = snprintf(buffer + len, buffer_char_count_max - len, "%s(%d): ", src_file, src_line);
// 			if( res < 0 )
// 				len = buffer_char_count_max;
// 			else
// 				len += res;
// 		}
// 	}
// 
// 	int sec;
// 	int ms;
// 	int mks;
// 	int ns;
// 
// 	FormatTime(tik, freq, &sec, &ms, &mks, &ns);
// 	if( len >= 0 && len < buffer_char_count_max )
// 		res = snprintf(buffer + len, buffer_char_count_max - len,
// 					   "%6.6u:%3.3u:%3.3u:%3.3u", int(sec), int(ms), int(mks), int(ns));
// 	if( res < 0 )
// 		len = buffer_char_count_max;
// 	else
// 		len += res;
// 
// 	if( options.use_thread )
// 	{
// 		auto thread_id = log->ThreadId();
// 		if( len >= 0 && len < buffer_char_count_max )
// 			res = snprintf(buffer + len, buffer_char_count_max - len,
// 						   " %8.8X", int(thread_id));
// 		if( res < 0 )
// 			len = buffer_char_count_max;
// 		else
// 			len += res;
// 	}
// 
// 	{
// 		if( len >= 0 && len < buffer_char_count_max )
// 			res = snprintf(buffer + len, buffer_char_count_max - len,
// 						   " %7.7u : %s : ", int(message_number), function_name);
// 		if( res < 0 )
// 			len = buffer_char_count_max;
// 		else
// 			len += res;
// 	}
// 
// 
// 
// 	if( len >= 0 && len < buffer_char_count_max )
// 		res = vsnprintf(buffer + len, buffer_char_count_max - len, format, ptr);
// 	if( res < 0 )
// 		len = buffer_char_count_max;
// 	else
// 		len += res;
// 
// 	if( len >= 0 && len < buffer_char_count_max )
// 		res = snprintf(buffer + len, buffer_char_count_max - len, "\r\n");
// 	if( res < 0 )
// 		len = buffer_char_count_max;
// 	else
// 		len += res;
// 
// 	if( res < 0 )
// 		buffer[buffer_char_count_max-1] = 0;
// 
// 	printed_char_count_without_null = len;
// 	log->WriteMessage(buffer, printed_char_count_without_null);
}