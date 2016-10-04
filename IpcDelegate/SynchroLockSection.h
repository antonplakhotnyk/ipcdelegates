#pragma once


class ISynchroLock
{
public:
	virtual void Enter() = 0;
	virtual void Leave() = 0;
};

// ���� � ������� ������ ���� CRITICAL_SECTION ������ �� ��� �� ��������
// ����� ��� �� ������� ��� �������� ��������� �������� �����������
// ���������� ������ �������������.
//
// ��������� ����������� new SynchroLock
// �� � ���� ������ �� ������� � �������, �� ����������� ������� ����������� ������.
// �.�. ��� ������������ ����� �������� � �������.
class SynchroLockSection{
public:
	SynchroLockSection(ISynchroLock* lock);
	~SynchroLockSection();

	void Enter(ISynchroLock* lock);
	void Leave();
private:
	ISynchroLock*	m_lock;
};

