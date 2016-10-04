#include "stdafx.h"
#include "DelegateWCaller_Simple.h"


DelegateWCaller_Simple::DelegateWCaller_Simple()
{
}


DelegateWCaller_Simple::~DelegateWCaller_Simple()
{
}

void DelegateWCaller_Simple::DeferredCall(DelegateWCaller::CallImp* call)
{
	m_call_que.push_back(call);
	PostRequest();
}

void DelegateWCaller_Simple::CancelCall(DelegateWCaller::CallImp* call)
{
	for( auto it = m_call_que.begin(); it!=m_call_que.end(); )
	{
		if( *it==call )
			it = m_call_que.erase(it);
		else
			it++;
	}
}

void DelegateWCaller_Simple::ProcessCalls()
{
	size_t max_call_count;

	MarkRequestProcessed();

	max_call_count = m_call_que.size();
	for( ; !m_call_que.empty() && (max_call_count!=0); max_call_count-- )
	{
		OPtr<DelegateWCaller::CallImp> call = m_call_que.front();
		m_call_que.pop_front();
		call->Invoke();
	}

	if( !m_call_que.empty() )
		PostRequest();
}

