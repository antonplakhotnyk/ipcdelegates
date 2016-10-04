#pragma once

#include "AVWeakBase.h"

namespace WPtrShared_NS
{


template<typename T1, typename T2, typename TYes, typename TNo>
class IsTypeEqual
{
private:
	template<typename T, typename TXYes, typename TXNo>
	class Check
	{
	public:
		typedef TNo Res;
	};

	template <typename TXYes, typename TXNo>
	class Check<T2, TXYes, TXNo>
	{
	public:
		typedef TYes Res;
	};

public:
	typedef typename Check<T1, TYes, TNo>::Res ResType;
};

template<typename TC, typename TYes, typename TNo>
struct IsTypeConst
{
	typedef typename IsTypeEqual<const TC, TC, TYes, TNo>::ResType ResType;
};

template<class T>
T* RefCounterPtrAssign(OPtr<WPtrShared_NS::SharedSpecific<T> >* this_p, T* lp)
{
	if( lp )
	{
		WPtrShared_NS::Shared* shared = lp->GetWeakShared();
		if( shared )
			*this_p = static_cast<WPtrShared_NS::SharedSpecific<T>*>(shared);
		else
		{
			WPtrShared_NS::SharedSpecific<T>* shared_specific = new WPtrShared_NS::SharedSpecific<T>(lp);
			lp->SetWeakShared(shared_specific);
			*this_p = shared_specific;
		}
	}
	else
		this_p->Release();

	return lp;
}

// ������� ������ ����������� ��������, ������ ����������. ����������� ���������
// ������ ����������� ��������� ��� ���� ������������.
//
// ������� ������ ��������� �� ������� ����� ������� � �� � ��� ����,
// ������� ��� ���� ��� ������� ������ ����������, � ������ �������� 
// ��������� ������� - �����������. �� ���� �������������� ���
// ������� AddRef � Release ����������� �������� �� �� ��� ��� ��������
// m_ref_count � ����� ������� delete this
template<class T>
class WPtrSharedBase
{
public:

	T* GetP() const
	{
		if( this->m_shared )
			return this->m_shared->Get();
		return NULL;
	}

// 	~WPtrSharedBase() throw()
// 	{
// 		Release();
// 	}

	template<class Q>
	operator Q*() const throw()
	{
		return GetP();
	}

	T& operator*() const throw()
	{
		T* tmp = GetP();
		XPtrBase_NS::CheckPointer(tmp!=NULL);
		return *tmp;
	}

	// ��������� MAC std-lib � ������� ���������� ���������� ����� �����������
	// ��������������� ��������� & �������� � ���� ��� 
	// ����������� � ���������� �� ����������. � ������� ����������� ��� ���������.
	// 		template<typename Tp> inline void Destroy(Tp* m_shared) { m_shared->~Tp(); }
	// 		template<typename Tp1, typename Tp2> inline void Construct(Tp1* m_shared, Tp2& val) {::new(static_cast<void*>(m_shared)) Tp1(val); }
	//
	// 	T** operator&() throw()
	// 	{
	// 		return Ref();
	// 	}

	operator bool()
	{
		return (GetP() != NULL);
	}

// 	bool operator!() const throw()
// 	{
// 		return (m_shared == NULL);
// 	}
	bool operator<(T* pT) const throw()
	{
		return GetP() < pT;
	}
	bool operator==(T* pT) const throw()
	{
		return GetP() == pT;
	}

	void Release() throw()
	{
		m_shared.Release();
	}

protected:
	OPtr<WPtrShared_NS::SharedSpecific<T> > m_shared;
};


template<typename T>
class WPtrSharedC: public WPtrSharedBase<T>
{
public:

	// ������ ������� � WPtrSharedV
	const T* operator->()const
	{
		if( this->m_shared )
			return this->GetP();
		XPtrBase_NS::CheckPointer(false);
		return NULL;
	}
};

template<typename T>
class WPtrSharedV: public WPtrSharedBase<T>
{
public:

	// ���� �������� ������ ���� �����������. ���� ����� ���� ��� ��
	// �������� � WPtr ������� ������������ �������, �� ���� ����� ����������� this 
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
	//
	// ��������� ������������� �������� ���������:
	//		������ ��������� ���������� (throw exception)
	//		� ��� ����� ���-�� ��� ���������.
	//		�� ��������� � �������� ���������, ���� ����� ��������� ����������.
	T* operator->()const
	{
		if( this->m_shared )
			return this->GetP();
		XPtrBase_NS::CheckPointer(false);
		return NULL;
	}
};


// ���� ��� ����� ������� ������ WPtr � WPtr � ������ ����� ����� � �����
// ����� ��� �� ��������� ������������ ��� � ������
template <class TCls>
class WPtr: public AVInternal_NS::IsTypeConst<TCls,
	WPtrShared_NS::WPtrSharedC<TCls>,
	WPtrShared_NS::WPtrSharedV<TCls> >::ResType
{
public:

	WPtr() throw()
	{
	}

	template <typename Q, template<typename>class QP>
	WPtr(const QP<Q>& lp) throw()
	{
		TCls* qlp = lp;
		WPtrShared_NS::RefCounterPtrAssign<TCls>(&this->m_shared, qlp);
	}

	// void* �� ������������ ������ ��� ����� ��������� �������� � ���� �������������� 
	// ������ ���� �������� ��������� ������ ���� ����� ������������ 
	// Release ��� =WPtr();
	// 	WPtr(int nNull) throw()
	// 	{
	// 		assert_if_not_equal(nNull,0);
	// 		(void)nNull;
	//         this->m_shared = NULL;
	// 	}
	//
	// ����������� ������� ������, ������� ��� ����������. 
	//
	// WPtr<Obj> obj(new Obj);// ������
	//
	// WPtr<Obj> obj1;
	// obj1.Attach(new Obj);// ���������
	// Obj* obj_tmp=obj1;
	// WPtr<Obj> obj2(obj_tmp);// ���������
	// 
	// ��� �� ��������� ��������������� ����������� ��������� ����� �������
	// Class():m_obj(new Obj){}// ������
	// ������������ ������ ��������� ������������������� ����������� ��������� ���
	// Class(Obj* obj):m_obj(obj){}// ���������
	//
	// � ��� ������ ��� �� �������� �������� ������, ������� ����������� �����������
	// ������� �� ��� �������� ���������� new ������� ������������� ����� ����������
	// �� ���� ���������� ��������.
	WPtr(TCls* lp) throw()
	{
		WPtrShared_NS::RefCounterPtrAssign<TCls>(&this->m_shared, lp);
	}

	WPtr(const WPtr<TCls>& lp) throw()
	{
		TCls* qlp = lp;
		WPtrShared_NS::RefCounterPtrAssign<TCls>(&this->m_shared, qlp);
	}

	TCls* operator=(TCls* lp) throw()
	{
		return WPtrShared_NS::RefCounterPtrAssign<TCls>(&this->m_shared, lp);
	}

	template <typename Q, template<typename>class QP>
	TCls* operator=(const QP<Q>& lp) throw()
	{
		return WPtrShared_NS::RefCounterPtrAssign<TCls>(&this->m_shared, lp);
	}

#ifdef PRESENT_FOR_VISUAL_ASSIST_BE_HAPPY__MUST_BE_UNDEFINED
	TCls operator->();
	void Release();
#endif
};

};// WPtrShared_NS


