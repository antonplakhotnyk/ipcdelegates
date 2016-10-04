#pragma once

	 
namespace AVInternal_NS
{

//-------------------------------------------------------

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

//-------------------------------------------------------

class Error_must_be_void_return_type;
class Error_must_be_static_function;
class Error_unsupported_function_signature;

class Error_Check
{
public:
	typedef int ResOk;
};

#if ( (_MSC_VER != 0) && (_MSC_VER < 1310) )// VC 7.1

template<typename T, typename TYes, typename TNo>
class IsVoid
{
private:
	template<typename T>
	struct Cmp
	{
		typedef TNo Res;
	};

	template<>
	struct Cmp<void>
	{
		typedef TYes Res;
	};

public:
	typedef typename Cmp<T>::Res Res;
};

#else
// gcc , VC 7.1+

template<typename T, typename TYes, typename TNo>
class IsVoid
{
public:
	typedef TNo Res;
};

template <typename TYes, typename TNo>
class IsVoid<void, TYes, TNo>
{
public:
	typedef TYes Res;
};

#endif

//-------------------------------------------------------
// 
// 
// template<class T>
// class IsRefType//NO
// {
// public:
// 
// 	template<typename TYes, typename TNo>
// 	class Res
// 	{
// 	public:
// 		typedef TNo Type;
// 	};
// };
// 
// template<class T>
// class IsRefType<T&>
// {
// public:
// 
// 	template<typename TYes, typename TNo>
// 	class Res
// 	{
// 	public:
// 		typedef TYes Type;
// 	};
// };
// 
//-------------------------------------------------------

template<typename T>
class NoRefType
{
public:
	typedef T Type;
};

template<typename T>
class NoRefType<T&>
{
public:
	typedef T Type;
};

//-------------------------------------------------------
template<class T>
class ValueRefType
{
public:
	typedef T& Type;
};

template<class T>
class ValueRefType<T&>
{
public:
	typedef T& Type;
};

template<class T>
class ValueRefType<T*>
{
public:
	typedef T* Type;
};

//-------------------------------------------------------

template<class T>
class ReturnNullIfRef
{
public:

	operator T()
	{
		return T();
	}
};

template<typename T>
class ReturnNullIfRef<T&>
{
public:

	operator T&()
	{
		return *(reinterpret_cast<typename NoRefType<T>::Type*>(NULL));
	}
};

//-------------------------------------------------------

template<typename THandProc, typename TYes, typename TNo>
class IsStaticProc
{
public:
	typedef TNo Res;
};


typedef char(&YesConst)[1];
typedef char(&NoConst)[2];


template<int TVal, typename TYes, typename TNo>
class DetectInt;

template<typename TYes, typename TNo>
class DetectInt<sizeof(YesConst), TYes, TNo>
{
public:

	typedef TYes ResType;
};

template<typename TYes, typename TNo>
class DetectInt<sizeof(NoConst), TYes, TNo>
{
public:
	typedef TNo ResType;
};


template<typename TDerived, typename TBase, typename TYes, typename TNo>
class IsBaseOf
{
private:

	static NoConst DetectProc(...);
	static YesConst DetectProc(const TBase*);

public:

	typedef typename DetectInt<sizeof(DetectProc((TDerived*)(NULL))), TYes, TNo>::ResType ResType;
};

template <class TCls>
class OPtr;

template<typename T>
class CRefCounter_Locker
{
public:

	CRefCounter_Locker(T* cls)
		:m_cls(cls)
	{
	}

	~CRefCounter_Locker()
	{
		m_cls.Release();
	}

private:

	OPtr<T> m_cls;
};


template<typename T>
class NoRefCount_Locker
{
public:

	NoRefCount_Locker(T* cls)
	{
	}

	~NoRefCount_Locker()
	{
	}

private:

};

template<typename TCls>
class RC_Lock
{
public:

	typedef typename IsBaseOf<TCls, AVRefCounter, CRefCounter_Locker<TCls>, NoRefCount_Locker<TCls> >::ResType ResType;
};

template<class T>
struct WptrLock
{
	typedef T Res;
};

template<template<class> class TWPtr, class T>
struct WptrLock<TWPtr<T> >
{
	typedef OPtr<T> Res;
};

template<template<class> class TWPtr, class T>
struct WptrLock<TWPtr<T>& >
{
	typedef OPtr<T> Res;
};


}// namespace AVInternal_NS