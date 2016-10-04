#include "StdAfx.h"
#include "SynchroLockSection.h"

SynchroLockSection::SynchroLockSection(ISynchroLock* lock)
:m_lock(NULL)
{
	Enter(lock);
}

SynchroLockSection::~SynchroLockSection()
{
	Leave();
}

void SynchroLockSection::Leave()
{
	if( m_lock==NULL )
		return;

	m_lock->Leave();
    m_lock=NULL;
//	m_lock.Release();
}

void SynchroLockSection::Enter(ISynchroLock* lock)
{
	Leave();

	m_lock=lock;
	return_if_equal(m_lock,NULL);
	m_lock->Enter();	
}

