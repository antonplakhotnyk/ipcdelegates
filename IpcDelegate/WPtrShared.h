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

// Подсчет ссылок константных объектов, должен проводится. Константные указатели
// должны копироватся оставаясь при этом константными.
//
// Подсчет ссылок относится ко времени жизни объекта а не к его типу,
// Поэтому тот факт что подсчет ссылок внутренний, а значит изменяет 
// состояние объекта - подавляется. То есть предполагается что
// функции AddRef и Release константные несмотря на то что они изменяют
// m_ref_count и могут вызвать delete this
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

	// Поскольку MAC std-lib и местами майкрософт использует такую конструкцию
	// переопределение оператора & приводит к тому что 
	// конструктор и деструктор не вызываются. А невызов деструктора это меморилик.
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

	// Смотри коменты к WPtrSharedV
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

	// Этот оператор должен быть константным. Чтоб можно было что то
	// получить у WPtr изнутри константного объекта, то есть через константрый this 
	// Но возвращаемый объект не должен быть константным, так как константность относится
	// к самому указателю, а не к тому, на что он указывает.
	// Аналогично этому случаю (который компилируется без ошибок)
	//		 class Cls
	//		 {
	//		 	void NonconstProc(){};
	//		 	void ConstProc() const {a->NonconstProc();}
	//		 	Cls* const a;
	//		 };
	//
	//
	// Обработка разименования нулевого указателя:
	//		должна порождать исключение (throw exception)
	//		С тем чтобы кто-то его обработал.
	//		Но обращение к нулевому указателю, само собой порождает исключение.
	T* operator->()const
	{
		if( this->m_shared )
			return this->GetP();
		XPtrBase_NS::CheckPointer(false);
		return NULL;
	}
};


// Есть ещё очень похожие классы WPtr и WPtr в случае фикса багов в одном
// нужно так же проверить аналогичьный баг в другом
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

	// void* не используется потому что любой указатель свободно в него конвертируется 
	// Вообще этот оператор неуместен вместо него нужно использовать 
	// Release или =WPtr();
	// 	WPtr(int nNull) throw()
	// 	{
	// 		assert_if_not_equal(nNull,0);
	// 		(void)nNull;
	//         this->m_shared = NULL;
	// 	}
	//
	// Увеличивает счетчик ссылок, работая как присвоение. 
	//
	// WPtr<Obj> obj(new Obj);// ОШИБКА
	//
	// WPtr<Obj> obj1;
	// obj1.Attach(new Obj);// ПРАВИЛЬНО
	// Obj* obj_tmp=obj1;
	// WPtr<Obj> obj2(obj_tmp);// ПРАВИЛЬНО
	// 
	// Это не позволяет сконструировать константный указатель таким образом
	// Class():m_obj(new Obj){}// ОШИБКА
	// Единственный способ правильно проинициализировать константный указатель это
	// Class(Obj* obj):m_obj(obj){}// ПРАВИЛЬНО
	//
	// А все потому что по правилам подсчета ссылок, счетчик увеличивает принимающая
	// сторона но при создании оператором new счетчик увеличивается самим оператором
	// то есть передающей стороной.
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


