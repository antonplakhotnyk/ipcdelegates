#pragma once

#include "AVInternal_NS.h"

namespace XPtrBase_NS
{

void CheckPointer(bool p);

// template<class T>
// T* Assign(T** this_p, T* lp) throw()
// {
// 	return_x_if_equal(this_p, NULL, lp);
// 	// В случае присвоения самого себе, экземпляр не должен уничтожится. Потому
// 	// сначала увеличиваем новый экзампляр, и только потом особождаем старый
// 	if( lp != NULL )
// 		lp->AddRef();
// 
// 	// Нужно сначала занулить, а потом удалить.
// 	// Иначе возможно рекурсивное удаление.
// 	// Потому что удаление это по сути CallBack с непредсказуемыми
// 	// последствиями.
// 	//
// 	// Если tmp->Release(); коственно удаляет this. Это произойдет если 
// 	// *this (т.е. XPtr ) содержится внутри класса *m_p (т.е. удаляемого екземпляра)
// 	// Этот же эффект может произойти при разрушении перекрестных ссылок.
// 	T* tmp = *this_p;
// 	*this_p = lp;
// 	if( tmp!=NULL )
// 		tmp->Release();
// 	return lp;
// }

// Подсчет ссылок константных объектов, должен проводится. Константные указатели
// должны копироватся оставаясь при этом константными.
//
// Подсчет ссылок относится ко времени жизни объекта а не к его типу,
// Поэтому тот факт что подсчет ссылок внутренний, а значит изменяет 
// состояние объекта - подавляется. То есть предполагается что
// функции AddRef и Release константные несмотря на то что они изменяют
// m_ref_count и могут вызвать delete this
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

	// Смотри коменты к XPtrV
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

	// Этот оператор должен быть константным. Чтоб можно было что то
	// получить у XPtr изнутри константного объекта, то есть через константрый this 
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
	// Обработка разименования нулевого указателя:
	//		должна порождать исключение (throw exception)
	//		С тем чтобы кто-то его обработал.
	//		Но обращение к нулевому указателю, само собой порождает исключение.
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


	// 	// Этот оператор не должен быть константным так как константный XPtrV 
	// 	// должен давать доступ только к константному внутреннему указателю T
	// 	//
	// 	// смотри комментарий "Обработка разименования нулевого указателя"
	// 	T* operator->()
	// 	{
	// 		if(this->m_p!=NULL)
	// 			return (this->GetP());
	// 		return_x(reinterpret_cast<T*>(NULL));
	// 	}
};


};// XPtrBase_NS

