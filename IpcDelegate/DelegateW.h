#pragma once

#include "AVRefCounter.h"
#include "OPtr.h"
#include "WPtr.h"
#include "AVPreprocessorRepeatJoin.h"
#include "AVInternal_NS.h"
#include "DelegateWCaller.h"
#include <list>

// * Поддержка константных функций в качестве обработчиков
// * Возможность отложеных вызовов
// * подмена порядка входных аргументов обработчика
// * подмена возвращаемого значения
// * замена входных аргументов и возвращаемого значения константами
// * Отсутствует копирование аргументов при вызове (не отложеном)
//		корректная работа с ссылочными типами
// * Копирование аргументов (по значению) при отложенном вызове
//		константные ссылки копируются как значения
//		неконстантные (возвращаемые значения) призводят к ошибке компиляции 
//		при попытке забиндить делегат с сигнатурой вызова содержащей неконстантные 
//		ссылки в параметрах отложеного вызова (аналогично возвращению не void)
// * ? В случае если делегат декларирует передачу аргумента по значению, 
//		а обработчик принимает этот аргумент по ссылке, обработчик получит копию
//		аргумента (так чтоб в случае цепочки обработчиков, модификация первым аргумента 
//		предыдущим обработчиком не влияла на значение полученое следующим)
// * Отложенный вызов игнорирует возвращаемое значение в остальном работает нормально
// * Конвертация типов при вызовеобработчика (если нужно и возможно)
// * Константные функции обработчики
// * Статические функции обработчиеки
// * Добавление обработчика в начало или в конец цепочки
// * Удаление/добавление обработчика цепочки обработчиков, в процессе вызова по этой цепочки
//		Должно корректно отрабатыватся даже если удаляется текущий элемент
// * В случае добавления в цепочку в процессе вызова через эту цепочку, 
//		новодобавленный элемент не вызывается при текущем проходе по цепочки, а
//		вызывается только при следующем вызове цепочки (даже если элемент был добавлен в конец)
//		и мог бы быть вызван при текущем вызове не нарушая порядка вызовов
//		Возможно это поведение должно быть другим.
// * ссылки возвращаются корректно (как ссылки)
// * обработчики содеражащие пустой WPtr очищаются функцией BindXAdd
// * Когда обработчик возвращает void а делегат int, при этом Del::Map указывает 
//		на необходимость вернуть значение функции т.е. сконвертировать void в int
//		нужно выдавать ВМЕНЯЕМУЮ ошибку компиляции
// * OK увеличивать счётчик ссылок хранящихся в нём констант на время вызова.
//
// * OK Отменяет вызов при неудачном локе аргументов, нужно указывать при бинде в параметрах констант
//
// * Нужно сделать проверки генерирующие вменяемые ошибки компиляции когда аргументы BindX несоответствующих типов
//		например когда в Bind передаётся адрес статической функции. Использовать type_traits

// Bind;
// BindS;
// BindD;
// BindE;
// BindES;
// BindED;
// BindAdd;
// BindSAdd;
// BindDAdd;
// BindEAdd;
// BindESAdd;
// BindEDAdd;

template<typename TDelProc, template<class> class TStorePtr>
class DelegateW;

namespace DelegateW_NS
{

void CheckThisCall(bool this_call);

struct DelConstStub
{
};

}// namespace DelegateW_NS

namespace Del
{

enum DelegateW_AddType { add_back, add_front };

// template<class P1=void, class P2=void>
// class Const;
template<REPEAT_JOIN_N_2(class P, AV_XN, void, AV_EQU_X, AV_COMA_DELEGATE, NUM_ARGS_MAX)>
class Const;

template<>
class Const<DelegateW_NS::DelConstStub>
{
};

template<class Del_T>
struct Require: public Del_T
{
	template<class Q>
	Require(const Q& q):Del_T(q){};
};

}// namespace Del

namespace DelegateW_NS
{

template<class TDelProc>
class InfoDelproc;

template<class THandProc>
class InfoHandproc;

template<class TDelegate>
class InfoDelegate;

// template<class THandProc>
// class Call;

template<class THandProc>
class Call_Selector;

template<typename THandProc>
class CallD;

template<class TDelProc>
class DelBase;

template<int TParam, class THP, class TCallData, class TConstData>
class SelArg;

template<int TParam, class TCallData, class TConstData>
class SelArgX;

template<int TParam, class TCallData, class TConstData>
struct SelArgType;


template<class TDelProc>
struct CallParamsDel;


template<class TDelProc>
struct CallParamsDeferredDel;

template<class THandProc>
class CallX;

template<class THandProc>
class CallX_RetVoidNo;

template<class THandProc>
class CallX_RetVoidAll;

template<class THandProc>
class CallX_RetVoidHand;

template<class THandProc>
class CallX_RetVoidDel;



template<class TDelegate>
class ImplD_RetVoidNo;

template<class TDelegate>
class ImplD_RetVoidAll;

template<class TDelegate>
class ImplD_RetVoidHand;

template<class TDelegate>
class ImplD_RetVoidDel;

//-------------------------------------------------------
template<class THandPtr>
struct InfoHandPtr;

template<template<class> class TPtr, class TP>
struct InfoHandPtr<TPtr<TP> >
{
	typedef TP THandClsType;
};

template<class TP>
struct InfoHandPtr<TP*>
{
	typedef TP THandClsType;
};

//-------------------------------------------------------

template<class TCheckType>
struct WptrLockCheck
{
	template<class T>
	static bool IsOk(register const T&)
	{
		return true;
	}
};

template<class TCheckType>
struct WptrLockCheck<Del::Require<TCheckType> >
{
	template<class T>
	static bool IsOk(const T& val)
	{
		return val;
	}
};

template<class TCheckType>
struct WptrLockCheck<Del::Require<TCheckType>& >
{
	template<class T>
	static bool IsOk(const T& val)
	{
		return val;
	}
};

template<class T>
struct WptrLock
{
	typedef T Res;
};

template<template<class> class TWPtr, class T>
struct WptrLock<Del::Require<TWPtr<T> > >
{
	typedef OPtr<T> Res;
};

template<template<class> class TWPtr, class T>
struct WptrLock<Del::Require<TWPtr<T> >& >
{
	typedef OPtr<T> Res;
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

//-------------------------------------------------------

template<class THandProc, class THandPtr, class TDelConst, template<class> class TStorePtr>
class CallX_DataMember
{
public:

	CallX_DataMember(const typename InfoHandproc<THandProc>::THandProcType& hand_proc_,
					 const THandPtr& hand_ptr_,
				 const TDelConst& call_const_):hand_proc(hand_proc_), hand_ptr(hand_ptr_), call_const(call_const_){};

	typename InfoHandproc<THandProc>::THandProcType hand_proc;
	TStorePtr<typename InfoHandPtr<THandPtr>::THandClsType> hand_ptr;
	TDelConst call_const;
};

template<class THandProc, class TDelConst, template<class> class TStorePtr>
class CallX_DataStatic
{
public:

	CallX_DataStatic(const typename InfoHandproc<THandProc>::THandProcType& hand_proc_,
					 const TDelConst& call_const_):hand_proc(hand_proc_), call_const(call_const_){};

	typename InfoHandproc<THandProc>::THandProcType hand_proc;
	TDelConst call_const;
};

template<class THandProc, class THandPtr, template<class> class TStorePtr>
class CallX_DataMember<THandProc, THandPtr, Del::Const<DelConstStub>, TStorePtr>
{
public:

	CallX_DataMember(const typename InfoHandproc<THandProc>::THandProcType& hand_proc_,
					 const THandPtr& hand_ptr_,
					 const Del::Const<DelConstStub>& call_const_):hand_proc(hand_proc_), hand_ptr(hand_ptr_) {};

	typename InfoHandproc<THandProc>::THandProcType hand_proc;
	TStorePtr<typename InfoHandPtr<THandPtr>::THandClsType> hand_ptr;
};

template<class THandProc, template<class> class TStorePtr>
class CallX_DataStatic<THandProc, Del::Const<DelConstStub>, TStorePtr>
{
public:

	CallX_DataStatic(const typename InfoHandproc<THandProc>::THandProcType& hand_proc_,
					 const Del::Const<DelConstStub>& call_const_):hand_proc(hand_proc_){};

	typename InfoHandproc<THandProc>::THandProcType hand_proc;
};

//-------------------------------------------------------

template<class TDelProc>
class CallBase: public AVRefCounter
{
public:
	typedef CallParamsDel<TDelProc> const& TInvokeArgType;
	typedef typename InfoDelproc<TDelProc>::TRetType TInvokeRetType;

	typedef TInvokeRetType(CallBase::*TInvokeProcType)(TInvokeArgType);

	virtual TInvokeRetType Invoke(TInvokeArgType data) const = 0;
	virtual bool AddHandler(CallBase* call, Del::DelegateW_AddType add_type){ return false; };
	virtual bool IsFilled(){ return false; };
};

}// namespace DelegateW_NS



#define INCLUDE_DELEGATEN_H

#define AV_NUM_ARGS 0
#include "DelegateW_N.h"
#define AV_NUM_ARGS 1
#include "DelegateW_N.h"
#define AV_NUM_ARGS 2
#include "DelegateW_N.h"
#define AV_NUM_ARGS 3
#include "DelegateW_N.h"
#define AV_NUM_ARGS 4
#include "DelegateW_N.h"
#define AV_NUM_ARGS 5
#include "DelegateW_N.h"
#define AV_NUM_ARGS 6
#include "DelegateW_N.h"
#define AV_NUM_ARGS 7
#include "DelegateW_N.h"
#define AV_NUM_ARGS 8
#include "DelegateW_N.h"

#undef INCLUDE_DELEGATEN_H

//-------------------------------------------------------


namespace DelegateW_NS
{

template<class TDelProc>
class CallE_Invoke: public DelegateWCaller::CallImp
{
private:

	OPtr<CallBase<TDelProc> > m_call;
	CallParamsDeferredDel<TDelProc> m_call_params;

private:


	void Invoke() override
	{
		const CallParamsDel<TDelProc>& data = m_call_params;
		m_call->Invoke(data);
	}


public:

	CallE_Invoke(const OPtr<CallBase<TDelProc> >& call, const CallParamsDel<TDelProc>& call_params):m_call(call), m_call_params(call_params)
	{
	}

};


template<class TDelProc>
class CallE: public CallBase<TDelProc>
{
private:

	OPtr<CallBase<TDelProc> > m_call;

public:

private:

	bool IsFilled() override
	{
		return m_call->IsFilled();
	};

	typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
	{
		auto new_call = new CallE_Invoke<TDelProc>(m_call, data);
		DelegateWCaller::GetDefault()->DeferredCall(new_call);
	}

public:

	CallE(CallBase<TDelProc>* call):m_call(call)
	{
	}

};


template<class TDelProc>
class Call_Multi: public CallBase<TDelProc>
{
private:

	// Вместо этого нужно сделать связаный список с безопасным автоматическим удалением элементов в процессе итерирования
	std::list<OPtr<CallBase<TDelProc> > > m_calls;

private:

	void ClearEmpty()
	{
		for( auto it = m_calls.begin(); it!=m_calls.end(); )
		{
			if( !(*it)->IsFilled() )
				it = m_calls.erase(it);
			else
				it++;
		}
	}

	bool IsFilled() override
	{
		for( auto it = m_calls.begin(); it!=m_calls.end(); it++ )
			if( (*it)->IsFilled() )
				return true;
		return false;
	};

	typename InfoDelproc<TDelProc>::TRetType Invoke(const CallParamsDel<TDelProc>& data) const override
	{
		for( auto it = m_calls.begin(); it!=m_calls.end(); it++)
			(*it)->Invoke(data);
	}

	bool AddHandler(CallBase<TDelProc>* call, Del::DelegateW_AddType add_type) override
	{ 
		ClearEmpty();
 		switch( add_type )
 		{
 			case Del::add_back: m_calls.push_back(call); break;
 			case Del::add_front: m_calls.insert(m_calls.begin(), call); break;
 		}

		return true; 
	};

public:

	Call_Multi(CallBase<TDelProc>* call)
	{
		AddHandler(call, Del::add_back);
	}
};





template<class TDelProc, class THandProc, class THandPtr, class TSigMap, class TDelConst, template<class> class TStorePtr>
class Impl_Selector
{
public:

	typedef typename
		AVInternal_NS::IsVoid<typename InfoDelproc<TDelProc>::TRetType,

		typename AVInternal_NS::IsVoid<typename InfoHandproc<THandProc>::TRetType,
		CallX_RetVoidAll<typename InfoHandproc<THandProc>::THandProcUnifiedType>,
		CallX_RetVoidDel<typename InfoHandproc<THandProc>::THandProcUnifiedType> >::Res,

		typename AVInternal_NS::IsVoid<typename InfoHandproc<THandProc>::TRetType,
		CallX_RetVoidHand<typename InfoHandproc<THandProc>::THandProcUnifiedType>,
		CallX_RetVoidNo<typename InfoHandproc<THandProc>::THandProcUnifiedType> >::Res
		>::

		Res::template ImplBase<TDelProc, THandProc, THandPtr, TSigMap, TDelConst, TStorePtr> CallXType;
};

//-------------------------------------------------------



template<class TDelProc, class TDelegate, class TSigMap, class TDelConst>
class ImplD_Selector
{
public:

	typedef typename
		AVInternal_NS::IsVoid<typename InfoDelproc<TDelProc>::TRetType,

		typename AVInternal_NS::IsVoid<typename InfoDelegate<TDelegate>::TRetType,
		typename ImplD_RetVoidAll<TDelegate>::template ImplBase<TDelProc, TDelegate, TSigMap, TDelConst>,
		typename ImplD_RetVoidDel<TDelegate>::template ImplBase<TDelProc, TDelegate, TSigMap, TDelConst> >::Res,

		typename AVInternal_NS::IsVoid<typename InfoDelegate<TDelegate>::TRetType,
		typename ImplD_RetVoidHand<TDelegate>::template ImplBase<TDelProc, TDelegate, TSigMap, TDelConst>,
		typename ImplD_RetVoidNo<TDelegate>::template ImplBase<TDelProc, TDelegate, TSigMap, TDelConst> >::Res
		>::

		Res CallXType;

};


} //namespace DelegateW_NS

//-------------------------------------------------------



template<typename TDelProc, template<class> class TStorePtr = WPtr>
class DelegateW: public DelegateW_NS::DelBase<TDelProc>
{
private:

	void AddHandler(DelegateW_NS::CallBase<TDelProc>* call, Del::DelegateW_AddType add_type)
	{ 
		if( call )
		{
			if( this->m_call )
			{
				while( true )
				{
					if( this->m_call->AddHandler(call, add_type) )
						break;

					this->m_call = new DelegateW_NS::Call_Multi<TDelProc>(this->m_call);
				}
			}
			else
				this->m_call = call;
		}
	}

public:

	operator bool() const
	{
		if( this->m_call )
			return this->m_call->IsFilled();
		return false;
	}

	void operator+= (const DelegateW& val)
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = val.m_call;
		AddHandler(new_call_base, Del::add_back);
	}

	//-------------------------------------------------------

	template<class TSigMap = Del::Map<>, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& Bind(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const = TDelConst())
	{
		CheckThisCall(this->m_call);
		this->m_call = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, THandPtr, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, hand_ptr, call_const);
		return *this;
	}

	template<class TSigMap = Del::Map<>, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindS(const THandProc& hand_proc, const TDelConst& call_const = TDelConst() )
	{
		CheckThisCall(this->m_call);
		this->m_call = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, void, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, call_const);
		return *this;
	}

	template<class TSigMap, template<class, template<class> class> class TDelegateDeduce, class TDelConst = Del::Const<DelegateW_NS::DelConstStub>, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindD(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const = TDelConst())
	{
		CheckThisCall(this->m_call);
		this->m_call = new typename DelegateW_NS::ImplD_Selector<TDelProc, TDelegateDeduce<TDelegateProc, TDelegateStorePtr>, TSigMap, TDelConst>::CallXType(del.m_call, call_const);
		return *this;
	}

	template<class TSigMap = Del::Map<>, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindE(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const = TDelConst())
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		CheckThisCall(this->m_call);
		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, THandPtr, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, hand_ptr, call_const);
		this->m_call = new DelegateW_NS::CallE<TDelProc>(new_call_base);
		return *this;
	}

	template<class TSigMap = Del::Map<>, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindES(const THandProc& hand_proc, const TDelConst& call_const = TDelConst() )
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		CheckThisCall(this->m_call);
		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, void, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, call_const);
		this->m_call = new DelegateW_NS::CallE<TDelProc>(new_call_base);
		return *this;
	}

	template<class TSigMap, template<class, template<class> class> class TDelegateDeduce, class TDelConst = Del::Const<DelegateW_NS::DelConstStub>, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindED(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const = TDelConst())
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		CheckThisCall(this->m_call);
		auto new_call_base = new typename DelegateW_NS::ImplD_Selector<TDelProc, TDelegateDeduce<TDelegateProc, TDelegateStorePtr>, TSigMap, TDelConst>::CallXType(del.m_call, call_const);
		this->m_call = new DelegateW_NS::CallE<TDelProc>(new_call_base);
		return *this;
	}

	template<class TSigMap, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type, const TDelConst& call_const = TDelConst())
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, THandPtr, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, hand_ptr, call_const);
		AddHandler(new_call_base, add_type);
		return *this;
	}

	template<class TSigMap, class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindSAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type, const TDelConst& call_const = TDelConst() )
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, void, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, call_const);
		AddHandler(new_call_base, add_type);
		return *this;
	}

	template<class TSigMap, template<class, template<class> class> class TDelegateDeduce, class TDelConst = Del::Const<DelegateW_NS::DelConstStub>, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type, const TDelConst& call_const = TDelConst() )
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::ImplD_Selector<TDelProc, TDelegateDeduce<TDelegateProc, TDelegateStorePtr>, TSigMap, TDelConst>::CallXType(del.m_call, call_const);
		AddHandler(new_call_base, add_type);
		return *this;
	}

	template<class TSigMap, class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindEAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type, const TDelConst& call_const = TDelConst())
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, THandPtr, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, hand_ptr, call_const);
		AddHandler(new DelegateW_NS::CallE<TDelProc>(new_call_base), add_type);
		return *this;
	}

	template<class TSigMap, class THandProc, class TDelConst>
	const DelegateW& BindESAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type, const TDelConst& call_const)
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::Impl_Selector<TDelProc, THandProc, void, TSigMap, TDelConst, TStorePtr>::CallXType(hand_proc, call_const);
		AddHandler(new DelegateW_NS::CallE<TDelProc>(new_call_base), add_type);
		return *this;
	}

	template<class TSigMap, template<class, template<class> class> class TDelegateDeduce, class TDelConst = Del::Const<DelegateW_NS::DelConstStub>, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type, const TDelConst& call_const)
	{
		typedef typename AVInternal_NS::IsVoid<typename DelegateW_NS::InfoDelproc<TDelProc>::TRetType, AVInternal_NS::Error_Check, AVInternal_NS::Error_must_be_void_return_type>::Res::ResOk ResOk;

		auto new_call_base = new typename DelegateW_NS::ImplD_Selector<TDelProc, TDelegateDeduce<TDelegateProc, TDelegateStorePtr>, TSigMap, TDelConst>::CallXType(del.m_call, call_const);
		AddHandler(new DelegateW_NS::CallE<TDelProc>(new_call_base), add_type);
		return *this;
	}

	//-------------------------------------------------------




	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindD(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr >& del, const TDelConst& call_const)
	{
		this->BindD<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, call_const);
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindD(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr >& del)
	{
		this->BindD<Del::Map<>, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, Del::Const<DelegateW_NS::DelConstStub>());
		return *this;
	}





	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindED(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
	{
		this->BindED<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, call_const);
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindED(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del)
	{
		this->BindED<Del::Map<>, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, Del::Const<DelegateW_NS::DelConstStub>());
		return *this;
	}

	template<class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
	{
		this->BindAdd<Del::Map<>, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, add_type, call_const);
		return *this;
	}

	template<class THandProc, class THandPtr, class TDelConst>
	const DelegateW& BindAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const)
	{
		this->BindAdd<Del::Map<>, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, Del::add_back, call_const);
		return *this;
	}


	template<class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindSAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
	{
		this->BindSAdd<Del::Map<>, THandProc, TDelConst >(hand_proc, add_type, call_const);
		return *this;
	}

	template<class THandProc, class TDelConst>
	const DelegateW& BindSAdd(const THandProc& hand_proc, const TDelConst& call_const)
	{
		this->BindSAdd<Del::Map<>, THandProc, TDelConst >(hand_proc, Del::add_back, call_const);
		return *this;
	}


	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr >
	const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = Del::Const<DelegateW_NS::DelConstStub>() )
	{
		this->BindDAdd<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, add_type, call_const);
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr >
	const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back)
	{
		this->BindDAdd<Del::Map<>, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, add_type, Del::Const<DelegateW_NS::DelConstStub>());
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
	{
		this->BindDAdd<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, Del::add_back, call_const);
		return *this;
	}


	template<class THandProc, class THandPtr, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindEAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
	{
		this->BindEAdd<Del::Map<>, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, add_type, call_const);
		return *this;
	}

	template<class THandProc, class THandPtr, class TDelConst>
	const DelegateW& BindEAdd(const THandProc& hand_proc, const THandPtr& hand_ptr, const TDelConst& call_const)
	{
		this->BindEAdd<Del::Map<>, THandProc, THandPtr, TDelConst >(hand_proc, hand_ptr, Del::add_back, call_const);
		return *this;
	}


	template<class THandProc, class TDelConst = Del::Const<DelegateW_NS::DelConstStub> >
	const DelegateW& BindESAdd(const THandProc& hand_proc, Del::DelegateW_AddType add_type = Del::add_back, const TDelConst& call_const = TDelConst())
	{
		this->BindESAdd<Del::Map<>, THandProc, TDelConst >(hand_proc, add_type, call_const);
		return *this;
	}

	template<class THandProc, class TDelConst>
	const DelegateW& BindESAdd(const THandProc& hand_proc, const TDelConst& call_const)
	{
		this->BindESAdd<Del::Map<>, THandProc, TDelConst >(hand_proc, Del::add_back, call_const);
		return *this;
	}


	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr >
	const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type, const TDelConst& call_const)
	{
		this->BindEDAdd<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, add_type, call_const);
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelegateProc, template<class> class TDelegateStorePtr >
	const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, Del::DelegateW_AddType add_type = Del::add_back)
	{
		this->BindEDAdd<Del::Map<>, TDelegateDeduce, Del::Const<DelegateW_NS::DelConstStub>, TDelegateProc, TDelegateStorePtr>(del, add_type, Del::Const<DelegateW_NS::DelConstStub>());
		return *this;
	}

	template<template<class, template<class> class> class TDelegateDeduce, class TDelConst, class TDelegateProc, template<class> class TDelegateStorePtr>
	const DelegateW& BindEDAdd(const TDelegateDeduce<TDelegateProc, TDelegateStorePtr>& del, const TDelConst& call_const)
	{
		this->BindEDAdd<Del::Map<>, TDelegateDeduce, TDelConst, TDelegateProc, TDelegateStorePtr>(del, Del::add_back, call_const);
		return *this;
	}

	//-------------------------------------------------------
	

#define INCLUDE_DELEGATEN_H

#define AV_NUM_ARGS 0
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 1
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 2
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 3
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 4
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 5
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 6
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 7
#include "DelegateW_N1.h"
#define AV_NUM_ARGS 8
#include "DelegateW_N1.h"

#undef INCLUDE_DELEGATEN_H

	

};