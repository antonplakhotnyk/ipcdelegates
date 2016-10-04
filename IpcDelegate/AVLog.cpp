#include "stdafx.h"
#include "AVLog.h"


AVLog* AVLog::s_instance = NULL;

AVLog::AVLog()
{
	// Кто последний создался, тот и активный
	// return_if_not_equal(s_instance, NULL);
	s_instance = this;
}


AVLog::~AVLog()
{
	if( s_instance == this )
		s_instance = NULL;
}

AVLog* AVLog::ActiveLogInstance()
{
	return s_instance;
}
