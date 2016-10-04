#pragma once


class ISynchroLock
{
public:
	virtual void Enter() = 0;
	virtual void Leave() = 0;
};

// Если в системе только одна CRITICAL_SECTION дедлок на ней не возможен
// Нужно так же помнить что прокачка сообщений содержит собственный
// внутренний объект синхронизации.
//
// Используя собственный new SynchroLock
// ни в коем случае не звонить в функции, за исключением функций копирования данных.
// т.к. это потэнциально может привести к дедлоку.
class SynchroLockSection{
public:
	SynchroLockSection(ISynchroLock* lock);
	~SynchroLockSection();

	void Enter(ISynchroLock* lock);
	void Leave();
private:
	ISynchroLock*	m_lock;
};

