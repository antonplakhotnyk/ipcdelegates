#pragma once

#include "DelegateWCaller_Simple.h"
#include <list>

class DelegateWCaller_Default: public DelegateWCaller_Simple
{
public:

	DelegateWCaller_Default(void);
	~DelegateWCaller_Default(void);

	using DelegateWCaller_Simple::ProcessCalls;

private:

	void PostRequest() override;
	void MarkRequestProcessed() override;

private:

	bool				m_request_posted;

};
