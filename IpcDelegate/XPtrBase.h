#pragma once

#include "AVInternal_NS.h"

namespace XPtrBase_NS
{

void CheckPointer(bool p);

// template<class T>
// T* Assign(T** this_p, T* lp) throw()
// {
// 	return_x_if_equal(this_p, NULL, lp);
// 	// � ������ ���������� ������ ����, ��������� �� ������ �����������. ������
// 	// ������� ����������� ����� ���������, � ������ ����� ���������� ������
// 	if( lp != NULL )
// 		lp->AddRef();
// 
// 	// ����� ������� ��������, � ����� �������.
// 	// ����� �������� ����������� ��������.
// 	// ������ ��� �������� ��� �� ���� CallBack � ����������������
// 	// �������������.
// 	//
// 	// ���� tmp->Release(); ��������� ������� this. ��� ���������� ���� 
// 	// *this (�.�. XPtr ) ���������� ������ ������ *m_p (�.�. ���������� ����������)
// 	// ���� �� ������ ����� ��������� ��� ���������� ������������ ������.
// 	T* tmp = *this_p;
// 	*this_p = lp;
// 	if( tmp!=NULL )
// 		tmp->Release();
// 	return lp;
// }

// ������� ������ ����������� ��������, ������ ����������. ����������� ���������
// ������ ����������� ��������� ��� ���� ������������.
//
// ������� ������ ��������� �� ������� ����� ������� � �� � ��� ����,
// ������� ��� ���� ��� ������� ������ ����������, � ������ �������� 
// ��������� ������� - �����������. �� ���� �������������� ���
// ������� AddRef � Release ����������� �������� �� �� ��� ��� ��������
// m_ref_count � ����� ������� delete this
template<class TCls, template<class> class TBase>
class XPtrBase: public TBase<TCls>
{
public:

	typedef TCls T;


	~XPtrBase() throw()
	{
		Release();
	}

	operator T*() const throw()
	{
		return this->GetP();
	}

	T& operator*() const throw()
	{
		T* p = this->GetP();
		CheckPointer(p!=NULL);
		return *p;
	}

	operator bool() const
	{
		return (this->GetP() != NULL);
	}

	bool operator==(bool b) const throw()
	{
		return (operator bool())==b;
	}

	template<template<class> class QPtr, class Q>
	bool operator<(const QPtr<Q>& other) const throw()
	{
		const void* vp = this->GetP();
		Q* other_p = other;
		const void* other_vp = other_p;
		return vp < other_vp;
	}

	template<class Q>
	bool operator<(Q* other) const throw()
	{
		const void* vp = this->GetP();
		const void* other_vp = other;
		return vp < other_vp;
	}

	template<template<class> class QPtr, class Q>
	bool operator==(const QPtr<Q>& other) const throw()
	{
		const void* vp = this->GetP();
		Q* other_p = other;
		const void* other_vp = other_p;
		return vp == other_vp;
	}

	template<class Q>
	bool operator==(Q* other) const throw()
	{
		const void* vp = this->GetP();
		const void* other_vp = other;
		return vp == other_vp;
	}

	template<template<class> class QPtr, class Q>
	bool operator!=(const QPtr<Q>& other) const throw()
	{
		const void* vp = this->GetP();
		Q* other_p = other;
		const void* other_vp = other_p;
		return vp != other_vp;
	}

	template<class Q>
	bool operator!=(Q* other) const throw()
	{
		const void* vp = this->GetP();
		const void* other_vp = other;
		return vp != other_vp;
	}

	void Release() throw()
	{
		this->Assign(NULL);
	}

};


template<typename TCls, template<class> class TBase>
class XPtrC: public XPtrBase<TCls, TBase>
{
public:
	typedef TCls T;

	// ������ ������� � XPtrV
	const T* operator->()const
	{
		T* p = this->GetP();
		CheckPointer(p!=NULL);
		return p;
	}

	const T* get()const
	{
		return this->GetP();
	}

};

template<typename TCls, template<class> class TBase>
class XPtrV: public XPtrBase<TCls, TBase>
{
public:
	typedef TCls T;

	// ���� �������� ������ ���� �����������. ���� ����� ���� ��� ��
	// �������� � XPtr ������� ������������ �������, �� ���� ����� ����������� this 
	// �� ������������ ������ �� ������ ���� �����������, ��� ��� ������������� ���������
	// � ������ ���������, � �� � ����, �� ��� �� ���������.
	// ���������� ����� ������ (������� ������������� ��� ������)
	//		 class Cls
	//		 {
	//		 	void NonconstProc(){};
	//		 	void ConstProc() const {a->NonconstProc();}
	//		 	Cls* const a;
	//		 };

	//
	// ��������� ������������� �������� ���������:
	//		������ ��������� ���������� (throw exception)
	//		� ��� ����� ���-�� ��� ���������.
	//		�� ��������� � �������� ���������, ���� ����� ��������� ����������.
	T* operator->()const
	{
		T* p = this->GetP();
		CheckPointer(p!=NULL);
		return p;
	}

	T* get()const
	{
		return this->GetP();
	}


	// 	// ���� �������� �� ������ ���� ����������� ��� ��� ����������� XPtrV 
	// 	// ������ ������ ������ ������ � ������������ ����������� ��������� T
	// 	//
	// 	// ������ ����������� "��������� ������������� �������� ���������"
	// 	T* operator->()
	// 	{
	// 		if(this->m_p!=NULL)
	// 			return (this->GetP());
	// 		return_x(reinterpret_cast<T*>(NULL));
	// 	}
};


};// XPtrBase_NS

