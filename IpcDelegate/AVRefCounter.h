#pragma once

#include "AtomicInt.h"

class AVRefCounter;

namespace OPtr_NS
{
template<class T>
class OPtrBase;
// template<class T>
// T* RefCounterPtrAssign(T** pp, T* lp) throw();
}



class AVRefCounter
{
protected:
	inline virtual ~AVRefCounter();
public:
	inline AVRefCounter();
	AVRefCounter(const AVRefCounter&);
	AVRefCounter& operator=(const AVRefCounter&);

	int GetRefCount() const;

	static void AfterAssignAddRefRelease(const AVRefCounter* addref, const AVRefCounter* release);


// private:
public:// ������ �� �������� AddRef Release ����������� ��������� ������� Assign
// 	template<class T>
// 	friend class OPtr_NS::OPtrBase;
//
// 	template<class T>
// 	friend T* OPtr_NS::RefCounterPtrAssign(T** pp, T* lp) throw();
//	friend void OPtr_NS::RefCounterPtrAssign(AVRefCounter** pp, AVRefCounter* lp) throw();


	// ��� �� ������ ������ ������ const ������ ��� m_ref_count �� ����� mutable
	// ��� ������� ������ ��� ����� ����� ����� ������� ��������� ���� ���
	// ����������� ��������.
	void AddRef() const;
	void Release() const;

private:
	// ��� ����� ��� ����������� �������� ����� ������� DLL
	// ��� ���������� ��������� ������ �������������� ��� ������,
	// ����� ������������ ���� ������� ��������� ������ ��� ������ 
	// ��� ����� ����� �������������� �������� new, � �������������� 
	// ���� ����� �������� ���������� ������.
	//
	// new �������� � ����� �����, � delete ���������� � ������
	// � ������ ������������ � ���������� ������ ����������� ���������� ������
	// ��� �������� �� ���������� ����������� �������� ������, � ����� ����������
	// �������� ������ ����. ���� ���� ���-�� ���������� � ������� DoDelete()=0
	// �.�. delete ����� � ������������ �����, � new ��� ������.
	// � ������ ����� ���� ������������� new ������ ��������� �����.
	// ���� �������������� delete � ���� ������ - ���� ��� ��� ������ 
	// ��������������� ��� new.
	virtual void SelfDelete() const;

private:
	// ��� ����� ��� ����������� ������� � ����������� ������ �����-�� 
	// ������������� �������� ����� ���������, ��� �� ������ ����������� 
	// ���� ��� ����������� ������� ������� ����������.
	virtual void OnSelfZeroRef()const{};
	virtual void Uninit(){};

private:

	mutable AtomicInt m_ref_count;
};

//-------------------------------------------------------
// ������ ���������� �����������
inline AVRefCounter::AVRefCounter(void):
	m_ref_count(0)
{
	// ��� ������ �� ����� ������ ��� ��������� �������� �������� ������
	// ������ � ������ ���������� ������� ����� 0 � ��� ������� ����������� ����� Attach
	//	AddRef();
}

inline AVRefCounter::~AVRefCounter()
{
}
