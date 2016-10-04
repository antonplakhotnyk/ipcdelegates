#pragma once

#include <atomic>

class AtomicInt
{
public:

	AtomicInt(int val):m_val(val){};

	inline void ref()
	{
		m_val.fetch_add(1);
	}

	inline bool deref()
	{
		return (m_val.fetch_sub(1)!=1);
	}

	inline int load()
	{
		return m_val.load();
	}

	inline int exchange(int val)
	{
		return m_val.exchange(val);
	}

private:

	std::atomic<int> m_val;
};
