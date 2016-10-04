#include "StdAfx.h"
#include "LockInt.h"

LockInt::LockInt(int* lock)
:m_lock(lock)
{
	(*m_lock)++;
}

LockInt::~LockInt()
{
	(*m_lock)--;
}

