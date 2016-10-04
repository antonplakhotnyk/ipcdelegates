#pragma once

#include "AVRefCounter.h"
#include "ThreadLocalStoregePtr.h"

//-------------------------------------------------------


class DelegateWCaller
{
public:

	class CallImp: public AVRefCounter
	{
	public:
		virtual void Invoke() = 0;
	};


	static DelegateWCaller* GetDefault();
	virtual void DeferredCall(DelegateWCaller::CallImp* call) = 0;

	~DelegateWCaller();

protected:

	DelegateWCaller();

private:

	static ThreadLocalStoregePtr<DelegateWCaller> s_instance;
};


//-------------------------------------------------------
