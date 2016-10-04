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
public:// Хорошо бы спрятать AddRef Release предоставив шаблонную функцию Assign
// 	template<class T>
// 	friend class OPtr_NS::OPtrBase;
//
// 	template<class T>
// 	friend T* OPtr_NS::RefCounterPtrAssign(T** pp, T* lp) throw();
//	friend void OPtr_NS::RefCounterPtrAssign(AVRefCounter** pp, AVRefCounter* lp) throw();


	// Это не совсем честно писать const потому что m_ref_count всё равно mutable
	// Так сделано потому что время жизни нужно считать правильно даже для
	// константных объектов.
	void AddRef() const;
	void Release() const;

private:
	// Это нужно для корректного удаления через границу DLL
	// Для реализации менеджера памяти специфического для класса,
	// нужно предоставить свою функцию выделения памяти для класса 
	// Для этого можно переопределить оператор new, и переопределить 
	// этот метод удаления екземпляра класса.
	//
	// new деляется в одном месте, а delete совершенно в другом
	// А значит потенциально в совершенно разных экземплярах менеджеров памяти
	// Это навязано не конкретной реализацией счетчика ссылок, а самой идеологией
	// удаление самого себя. Даже если как-то изловчится и сделать DoDelete()=0
	// т.к. delete будет в фиксированом месте, а new где попало.
	// А значит нужно либо зафиксировать new сделав фабричный метод.
	// Либо переадресовать delete в куда попало - туда где был сделан 
	// соответствующий ему new.
	virtual void SelfDelete() const;

private:
	// Это нужно для возможности сделать в производном классе какие-то 
	// специфические действия перед удалением, ещё до вызова деструктора 
	// пока ещё виртуальная таблица функций корректная.
	virtual void OnSelfZeroRef()const{};
	virtual void Uninit(){};

private:

	mutable AtomicInt m_ref_count;
};

//-------------------------------------------------------
// Смотри копирующий конструктор
inline AVRefCounter::AVRefCounter(void):
	m_ref_count(0)
{
	// Это больше не нужно потому что поменялся механизм подсчёта ссылок
	// Теперь у нового экземпляра счетчик равен 0 и его ненужно присваивать через Attach
	//	AddRef();
}

inline AVRefCounter::~AVRefCounter()
{
}
