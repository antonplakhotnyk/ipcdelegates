#include "stdafx.h"
#include "DelegateWCaller.h"


ThreadLocalStoregePtr<DelegateWCaller> DelegateWCaller::s_instance;

DelegateWCaller::DelegateWCaller()
{
	return_if_not_equal(s_instance, NULL);
	s_instance = this;
}

DelegateWCaller::~DelegateWCaller()
{
	return_if_not_equal(s_instance, this);
	s_instance = NULL;
}

DelegateWCaller* DelegateWCaller::GetDefault()
{
	return_x_if_equal(s_instance,NULL,NULL);
	return s_instance;
}
