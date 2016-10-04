#include "StdAfx.h"
#include "DelegateWCaller_Default.h"

DelegateWCaller_Default::DelegateWCaller_Default(void)
:m_request_posted(false)
{
}

DelegateWCaller_Default::~DelegateWCaller_Default(void)
{
}

void DelegateWCaller_Default::PostRequest()
{
	m_request_posted = true;
}

void DelegateWCaller_Default::MarkRequestProcessed()
{
	m_request_posted = false;
}