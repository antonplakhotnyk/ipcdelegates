#include "StdAfx.h"
#include "ErrorPool.h"
#include "ThreadLocalStoregePtr.h"

// 	__declspec(thread) нельзя использовать это не работает из dll загруженной по LoadLibrary
//		Нужно использовать Tls
//
// MSDN Determine Which Linking Method to Use
//		If a DLL declares static-extent data as __declspec(thread), it can cause a 
//		protection fault if explicitly linked. After the DLL is loaded with 
//		LoadLibrary, it causes a protection fault whenever the code references 
//		this data. (Static-extent data includes both global and local static items.) 
//		Therefore, when you create a DLL, you should either avoid using thread-local 
//		storage, or inform DLL users about potential pitfalls (in case they attempt 
//		dynamic loading). 
static ThreadLocalStoregePtr<ErrorPool> s_pool_list_back;

ErrorPool::ErrorPool(void)
{
	// добавили себя в конец списка.
	m_previous=s_pool_list_back;
	s_pool_list_back=this;
}

ErrorPool::~ErrorPool(void)
{
	s_pool_list_back=m_previous;// удаление себя из списка
	if(m_data.raised)
	{
		return_if_equal(s_pool_list_back,NULL);// Остался не обработанный асерт
		s_pool_list_back->m_data=m_data;
	}
}

bool ErrorPool::Raise(const char* file, int line, const char* func)
{
	if(s_pool_list_back==NULL)
		return true;

	check_point("Handled from %s %u %s", (const char*)(file), int(line), (const char*)(func));

	s_pool_list_back->m_data.file=file;
	s_pool_list_back->m_data.line=line;
	s_pool_list_back->m_data.func=func;
	s_pool_list_back->m_data.raised=true;

	return false;
}

bool ErrorPool::IsRaisedClear()
{
	bool ret=m_data.raised;
	m_data.raised=false;
	return ret;
}

bool ErrorPool::IsRaised()
{
	return m_data.raised;
}
