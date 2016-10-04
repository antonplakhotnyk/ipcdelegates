#pragma once


template<class TCls>
class ThreadLocalStoregePtr
{
public:

	ThreadLocalStoregePtr()
		:m_ptr(0)
	{
	}

	operator TCls*()
	{
		return m_ptr;
	}

	TCls* operator->()
	{
		return m_ptr;
	}

	void operator=(TCls* val)
	{
		m_ptr=val;
	}

private:

	TCls* m_ptr;
};
