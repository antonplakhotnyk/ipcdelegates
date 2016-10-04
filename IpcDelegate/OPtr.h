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
		// Нужно сначала занулить, а потом удалить.
		// Иначе возможно рекурсивное удаление.
		// Потому что удаление это по сути CallBack с непредсказуемыми
		// последствиями.
		//
		// Если tmp->Release(); коственно удаляет this. Это произойдет если 
		// *this (т.е. XPtr ) содержится внутри класса *m_p (т.е. удаляемого екземпляра)
		// Этот же эффект может произойти при разрушении перекрестных ссылок.

		T* old_p = m_p;
		m_p = new_p;
		AVRefCounter::AfterAssignAddRefRelease(new_p, old_p);
	}

};

}

// Есть очень похожий класс NOPtr
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
// // 	// В случае присвоения самого себе, экземпляр не должен уничтожится. Потому
// // 	// сначала увеличиваем новый экзампляр, и только потом особождаем старый
// // 	if( lp != NULL )
// // 		lp->AddRef();
// // 
// // 	// Нужно сначала занулить, а потом удалить.
// // 	// Иначе возможно рекурсивное удаление.
// // 	// Потому что удаление это по сути CallBack с непредсказуемыми
// // 	// последствиями.
// // 	//
// // 	// Если tmp->Release(); коственно удаляет this. Это произойдет если 
// // 	// *this (т.е. OPtr ) содержится внутри класса *m_p (т.е. удаляемого екземпляра)
// // 	// Этот же эффект может произойти при разрушении перекрестных ссылок.
// // 	T* tmp = *this_p;
// // 	*this_p = lp;
// // 	if( tmp!=NULL )
// // 		tmp->Release();
// // 	return lp;
// // }
// 
// // Подсчет ссылок константных объектов, должен проводится. Константные указатели
// // должны копироватся оставаясь при этом константными.
// //
// // Подсчет ссылок относится ко времени жизни объекта а не к его типу,
// // Поэтому тот факт что подсчет ссылок внутренний, а значит изменяет 
// // состояние объекта - подавляется. То есть предполагается что
// // функции AddRef и Release константные несмотря на то что они изменяют
// // m_ref_count и могут вызвать delete this
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
// 		// Адрес внутренней переменной выдается наружу, чтоб в эту переменную
// 		// что-то записали. Перед этим переменную нужно обнулить.
// 		//
// 		// Адрес внутренней переменной вообще не должен выдаватся наружу.
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
// 	// Поскольку MAC std-lib и местами майкрософт использует такую конструкцию
// 	// переопределение оператора & приводит к тому что 
// 	// конструктор и деструктор не вызываются. А невызов деструктора это меморилик.
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
// 		// Нужно сначала занулить, а потом удалить.
// 		// Иначе возможно рекурсивное удаление.
// 		// Потому что удаление это по сути CallBack с непредсказуемыми
// 		// последствиями.
// 		//
// 		// Если tmp->Release(); коственно удаляет this. Это произойдет если 
// 		// *this (т.е. OPtr ) содержится внутри класса *m_p (т.е. удаляемого екземпляра)
// 		// Этот же эффект может произойти при разрушении перекрестных ссылок.
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
// 	// Смотри коменты к OPtrV
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
// 	// Этот оператор должен быть константным. Чтоб можно было что то
// 	// получить у OPtr изнутри константного объекта, то есть через константрый this 
// 	// Но возвращаемый объект не должен быть константным, так как константность относится
// 	// к самому указателю, а не к тому, на что он указывает.
// 	// Аналогично этому случаю (который компилируется без ошибок)
// 	//		 class Cls
// 	//		 {
// 	//		 	void NonconstProc(){};
// 	//		 	void ConstProc() const {a->NonconstProc();}
// 	//		 	Cls* const a;
// 	//		 };
// 
// 	//
// 	// Обработка разименования нулевого указателя:
// 	//		должна порождать исключение (throw exception)
// 	//		С тем чтобы кто-то его обработал.
// 	//		Но обращение к нулевому указателю, само собой порождает исключение.
// 	T* operator->()const
// 	{
// 		if( this->m_p!=NULL )
// 			return this->GetP();
// 		return_x(reinterpret_cast<T*>(NULL));
// 	}
// 
// 	// 	// Этот оператор не должен быть константным так как константный OPtrV 
// 	// 	// должен давать доступ только к константному внутреннему указателю T
// 	// 	//
// 	// 	// смотри комментарий "Обработка разименования нулевого указателя"
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
// // Есть ещё очень похожие классы OPtr и OPtr в случае фикса багов в одном
// // нужно так же проверить аналогичьный баг в другом
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
// 	// void* не используется потому что любой указатель свободно в него конвертируется 
// 	// Вообще этот оператор неуместен вместо него нужно использовать 
// 	// Release или =OPtr();
// 	// 	OPtr(int nNull) throw()
// 	// 	{
// 	// 		assert_if_not_equal(nNull,0);
// 	// 		(void)nNull;
// 	//         this->m_p = NULL;
// 	// 	}
// 
// 	// Увеличивает счетчик ссылок, работая как присвоение. 
// 	//
// 	// OPtr<Obj> obj(new Obj);// ОШИБКА
// 	//
// 	// OPtr<Obj> obj1;
// 	// obj1.Attach(new Obj);// ПРАВИЛЬНО
// 	// Obj* obj_tmp=obj1;
// 	// OPtr<Obj> obj2(obj_tmp);// ПРАВИЛЬНО
// 	// 
// 	// Это не позволяет сконструировать константный указатель таким образом
// 	// Class():m_obj(new Obj){}// ОШИБКА
// 	// Единственный способ правильно проинициализировать константный указатель это
// 	// Class(Obj* obj):m_obj(obj){}// ПРАВИЛЬНО
// 	//
// 	// А все потому что по правилам подсчета ссылок, счетчик увеличивает принимающая
// 	// сторона но при создании оператором new счетчик увеличивается самим оператором
// 	// то есть передающей стороной.
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
