#pragma once

#include "DelegateWCaller.h"
#include <list>
#include "OPtr.h"


class DelegateWCaller_Simple: public DelegateWCaller
{
public:
	DelegateWCaller_Simple();
	~DelegateWCaller_Simple();

protected:

	void ProcessCalls();
	void CancelCall(DelegateWCaller::CallImp* call);


private:

	virtual void PostRequest() = 0;
	virtual void MarkRequestProcessed() = 0;

private:

	void DeferredCall(DelegateWCaller::CallImp* call) override;

private:

	std::list<OPtr<DelegateWCaller::CallImp> > m_call_que;
};
