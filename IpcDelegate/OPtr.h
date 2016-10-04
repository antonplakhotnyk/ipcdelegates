#pragma once

#include "XPtrBase.h"

namespace OPtr_NS
{

template<class T>
class Base
{
protected:
	T* m_p = {NULL};

protected:

	T* GetP() const
	{
		return this->m_p;
	}

	void Assign(T* new_p)
	{
		// ����� ������� ��������, � ����� �������.
		// ����� �������� ����������� ��������.
		// ������ ��� �������� ��� �� ���� CallBack � ����������������
		// �������������.
		//
		// ���� tmp->Release(); ��������� ������� this. ��� ���������� ���� 
		// *this (�.�. XPtr ) ���������� ������ ������ *m_p (�.�. ���������� ����������)
		// ���� �� ������ ����� ��������� ��� ���������� ������������ ������.

		T* old_p = m_p;
		m_p = new_p;
		AVRefCounter::AfterAssignAddRefRelease(new_p, old_p);
	}

};

}

// ���� ����� ������� ����� NOPtr
template <class TCls>
class OPtr: public AVInternal_NS::IsTypeConst<TCls,
	XPtrBase_NS::XPtrC<TCls, OPtr_NS::Base>,
	XPtrBase_NS::XPtrV<TCls, OPtr_NS::Base> >::ResType
{
public:


	OPtr() throw()
	{
	}

	template <typename Q, template<typename>class QP>
	OPtr(const QP<Q>& lp) throw()
	{
		this->Assign(lp);
	}

	OPtr(TCls* lp) throw()
	{
		this->Assign(lp);
	}

	OPtr(const OPtr<TCls>& lp) throw()
	{
		this->Assign(lp);
	}

	TCls* operator=(const OPtr<TCls>& lp) throw()
	{
		this->Assign(lp);
		return this->GetP();
	}

	TCls* operator=(TCls* lp) throw()
	{
		this->Assign(lp);
		return this->GetP();
	}

	template <typename Q, template<typename>class QP>
	TCls* operator=(const QP<Q>& lp) throw()
	{
		this->Assign(lp);
		return this->GetP();
	}


#ifdef PRESENT_FOR_VISUAL_ASSIST_BE_HAPPY__MUST_BE_UNDEFINED
	TCls operator->();
	void Release();
#endif
};


// template<class TCls>
// using XPtr<TCls, OPtrBase<TCls> > OPtr;



// namespace OPtr_NS
// {
// 
// template<typename T1, typename T2, typename TYes, typename TNo>
// class IsTypeEqual
// {
// private:
// 	template<typename T, typename TXYes, typename TXNo>
// 	class Check
// 	{
// 	public:
// 		typedef TNo Res;
// 	};
// 
// 	template <typename TXYes, typename TXNo>
// 	class Check<T2, TXYes, TXNo>
// 	{
// 	public:
// 		typedef TYes Res;
// 	};
// 
// public:
// 	typedef typename Check<T1, TYes, TNo>::Res ResType;
// };
// 
// template<typename TC, typename TYes, typename TNo>
// struct IsTypeConst
// {
// 	typedef typename IsTypeEqual<const TC, TC, TYes, TNo>::ResType ResType;
// };
// 
// // template<class T>
// // T* Assign(T** this_p, T* lp) throw()
// // {
// // 	return_x_if_equal(this_p, NULL, lp);
// // 	// � ������ ���������� ������ ����, ��������� �� ������ �����������. ������
// // 	// ������� ����������� ����� ���������, � ������ ����� ���������� ������
// // 	if( lp != NULL )
// // 		lp->AddRef();
// // 
// // 	// ����� ������� ��������, � ����� �������.
// // 	// ����� �������� ����������� ��������.
// // 	// ������ ��� �������� ��� �� ���� CallBack � ����������������
// // 	// �������������.
// // 	//
// // 	// ���� tmp->Release(); ��������� ������� this. ��� ���������� ���� 
// // 	// *this (�.�. OPtr ) ���������� ������ ������ *m_p (�.�. ���������� ����������)
// // 	// ���� �� ������ ����� ��������� ��� ���������� ������������ ������.
// // 	T* tmp = *this_p;
// // 	*this_p = lp;
// // 	if( tmp!=NULL )
// // 		tmp->Release();
// // 	return lp;
// // }
// 
// // ������� ������ ����������� ��������, ������ ����������. ����������� ���������
// // ������ ����������� ��������� ��� ���� ������������.
// //
// // ������� ������ ��������� �� ������� ����� ������� � �� � ��� ����,
// // ������� ��� ���� ��� ������� ������ ����������, � ������ �������� 
// // ��������� ������� - �����������. �� ���� �������������� ���
// // ������� AddRef � Release ����������� �������� �� �� ��� ��� ��������
// // m_ref_count � ����� ������� delete this
// template<class TCls>
// class OPtrBase
// {
// public:
// 
// 	typedef TCls T;
// 
// 	T* GetP() const
// 	{
// 		return this->m_p;
// 	}
// 
// 	OPtrBase() throw()
// 		:m_p(NULL)
// 	{
// 	}
// 
// 	~OPtrBase() throw()
// 	{
// 		Release();
// 	}
// 
// 	operator T*() const throw()
// 	{
// 		return GetP();
// 	}
// 
// 	T& operator*() const throw()
// 	{
// 		return_x_if_equal(m_p, NULL, *((T*)(NULL)));
// 		return *m_p;
// 	}
// 
// 	T** Ref()
// 	{
// 		// ����� ���������� ���������� �������� ������, ���� � ��� ����������
// 		// ���-�� ��������. ����� ���� ���������� ����� ��������.
// 		//
// 		// ����� ���������� ���������� ������ �� ������ ��������� ������.
// 		Release();
// 		return &m_p;
// 	}
// 
// 	TCls& Raw() const
// 	{
// 		return_x_if_equal(m_p, NULL, *((TCls*)(NULL)));
// 		return *m_p;
// 	}
// 
// 	// ��������� MAC std-lib � ������� ���������� ���������� ����� �����������
// 	// ��������������� ��������� & �������� � ���� ��� 
// 	// ����������� � ���������� �� ����������. � ������� ����������� ��� ���������.
// 	// 		template<typename Tp> inline void Destroy(Tp* m_p) { m_p->~Tp(); }
// 	// 		template<typename Tp1, typename Tp2> inline void Construct(Tp1* m_p, Tp2& val) {::new(static_cast<void*>(m_p)) Tp1(val); }
// 	//
// 	// 	T** operator&() throw()
// 	// 	{
// 	// 		return Ref();
// 	// 	}
// 
// 	operator bool() const
// 	{
// 		return (m_p != NULL);
// 	}
// 
// // 	bool operator!() const throw()
// // 	{
// // 		return (m_p == NULL);
// // 	}
// 	bool operator<(T* pT) const throw()
// 	{
// 		return GetP() < pT;
// 	}
// 
// 	bool operator==(bool b) const throw()
// 	{
// 		return operator bool();
// 	}
// 
// 	bool operator==(T* pT) const throw()
// 	{
// 		return GetP() == pT;
// 	}
// 
// 	void Release() throw()
// 	{
//   		Assign(NULL); 
// 	}
// 
// protected:
// 	TCls* m_p;
// 
// protected:
// 
// 	void Assign(T* new_p)
// 	{
// 		// ����� ������� ��������, � ����� �������.
// 		// ����� �������� ����������� ��������.
// 		// ������ ��� �������� ��� �� ���� CallBack � ����������������
// 		// �������������.
// 		//
// 		// ���� tmp->Release(); ��������� ������� this. ��� ���������� ���� 
// 		// *this (�.�. OPtr ) ���������� ������ ������ *m_p (�.�. ���������� ����������)
// 		// ���� �� ������ ����� ��������� ��� ���������� ������������ ������.
// 
// 		T* old_p = m_p;
// 		m_p = new_p;
// 		AVRefCounter::AfterAssignAddRefRelease(new_p, old_p);
// 	}
// 
// };
// 
// 
// template<typename TCls>
// class OPtrC: public OPtrBase<TCls>
// {
// public:
// 	typedef TCls T;
// 
// 	// ������ ������� � OPtrV
// 	const T* operator->()const
// 	{
// 		if( this->m_p!=NULL )
// 			return this->GetP();
// 		return_x(reinterpret_cast<T*>(NULL));
// 	}
// };
// 
// template<typename TCls>
// class OPtrV: public OPtrBase<TCls>
// {
// public:
// 	typedef TCls T;
// 
// 	// ���� �������� ������ ���� �����������. ���� ����� ���� ��� ��
// 	// �������� � OPtr ������� ������������ �������, �� ���� ����� ����������� this 
// 	// �� ������������ ������ �� ������ ���� �����������, ��� ��� ������������� ���������
// 	// � ������ ���������, � �� � ����, �� ��� �� ���������.
// 	// ���������� ����� ������ (������� ������������� ��� ������)
// 	//		 class Cls
// 	//		 {
// 	//		 	void NonconstProc(){};
// 	//		 	void ConstProc() const {a->NonconstProc();}
// 	//		 	Cls* const a;
// 	//		 };
// 
// 	//
// 	// ��������� ������������� �������� ���������:
// 	//		������ ��������� ���������� (throw exception)
// 	//		� ��� ����� ���-�� ��� ���������.
// 	//		�� ��������� � �������� ���������, ���� ����� ��������� ����������.
// 	T* operator->()const
// 	{
// 		if( this->m_p!=NULL )
// 			return this->GetP();
// 		return_x(reinterpret_cast<T*>(NULL));
// 	}
// 
// 	// 	// ���� �������� �� ������ ���� ����������� ��� ��� ����������� OPtrV 
// 	// 	// ������ ������ ������ ������ � ������������ ����������� ��������� T
// 	// 	//
// 	// 	// ������ ����������� "��������� ������������� �������� ���������"
// 	// 	T* operator->()
// 	// 	{
// 	// 		if(this->m_p!=NULL)
// 	// 			return (this->GetP());
// 	// 		return_x(reinterpret_cast<T*>(NULL));
// 	// 	}
// };
// 
// };// OPtr_NS
// 
// // ���� ��� ����� ������� ������ OPtr � OPtr � ������ ����� ����� � �����
// // ����� ��� �� ��������� ������������ ��� � ������
// template <class TCls>
// class OPtr: public OPtr_NS::IsTypeConst<TCls,
// 	OPtr_NS::OPtrC<TCls>,
// 	OPtr_NS::OPtrV<TCls> >::ResType
// {
// public:
// 
// 	typedef TCls T;
// 
// 	OPtr() throw()
// 	{
// 	}
// 
// 	template <typename Q, template<typename>class QP>
// 	OPtr(const QP<Q>& lp) throw()
// 	{
// 		this->Assign(lp);
// 	}
// 
// 	operator OPtr<T>()
// 	{
// 		return OPtr<T>(this->GetP());
// 	}
// 
// 	// void* �� ������������ ������ ��� ����� ��������� �������� � ���� �������������� 
// 	// ������ ���� �������� ��������� ������ ���� ����� ������������ 
// 	// Release ��� =OPtr();
// 	// 	OPtr(int nNull) throw()
// 	// 	{
// 	// 		assert_if_not_equal(nNull,0);
// 	// 		(void)nNull;
// 	//         this->m_p = NULL;
// 	// 	}
// 
// 	// ����������� ������� ������, ������� ��� ����������. 
// 	//
// 	// OPtr<Obj> obj(new Obj);// ������
// 	//
// 	// OPtr<Obj> obj1;
// 	// obj1.Attach(new Obj);// ���������
// 	// Obj* obj_tmp=obj1;
// 	// OPtr<Obj> obj2(obj_tmp);// ���������
// 	// 
// 	// ��� �� ��������� ��������������� ����������� ��������� ����� �������
// 	// Class():m_obj(new Obj){}// ������
// 	// ������������ ������ ��������� ������������������� ����������� ��������� ���
// 	// Class(Obj* obj):m_obj(obj){}// ���������
// 	//
// 	// � ��� ������ ��� �� �������� �������� ������, ������� ����������� �����������
// 	// ������� �� ��� �������� ���������� new ������� ������������� ����� ����������
// 	// �� ���� ���������� ��������.
// 	OPtr(TCls* lp) throw()
// 	{
//  		this->Assign(lp);
// 	}
// 	/*
// 	template <typename Q>
// 	OPtr(Q* lp)
// 	{
// 	if (lp != NULL)
// 	lp->QueryInterface(__uuidof(Q), (void**)&this->m_p);
// 	else
// 	this->m_p = NULL;
// 	}
// 	template <>
// 	*/
// 	OPtr(const OPtr<TCls>& lp) throw()
// 	{
// 		this->Assign(lp);
// 	}
// 
// 
// 	// 	TCls* operator=(void* lp)
// 	// 	{
// 	//     return (TCls*)AtlComPtrAssign((IUnknown**)&this->m_p, (TCls*)lp);
// 	// 	}
// 	// 	template <typename Q>
// 	// 	TCls* operator=(Q* lp)
// 	// 	{
// 	//     return (TCls*)AtlComQIPtrAssign((IUnknown**)&this->m_p, lp, __uuidof(TCls));
// 	// 	}
// 
// 
// 
// 	TCls* operator=(TCls* lp) throw()
// 	{
// 		this->Assign(lp);
// 		return this->GetP();
// 	}
// 	template <typename Q, template<typename>class QP>
// 	TCls* operator=(const QP<Q>& lp) throw()
// 	{
// 		this->Assign(lp);
// 		return this->GetP();
// 	}
// 	TCls* operator=(const OPtr<TCls>& lp) throw()
// 	{
// 		this->Assign(lp.m_p);
// 		return this->GetP();
// 	}
// 
// #ifdef PRESENT_FOR_VISUAL_ASSIST_BE_HAPPY__MUST_BE_UNDEFINED
// 	TCls& Raw();
// 	TCls operator->();
// 	void Release();
// 	void CopyTo(TCls**);
// #endif
// };
// 
