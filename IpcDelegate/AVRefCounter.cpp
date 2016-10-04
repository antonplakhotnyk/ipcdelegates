#include "stdafx.h"
#include "AVRefCounter.h"


// Счетчик ссылок, индивидуальный у каждой копии объекта и
// его нельзя копировать, так как это нарушит подсчет ссылок.
// Это не влияет на механизм и возможность копирования остальной части 
// производного класса
//
// m_naked_delete_notify тоже индевидуален, так же как и счётчик ссылок.
AVRefCounter::AVRefCounter(const AVRefCounter&):
m_ref_count(0)
{
	// То же самое что и в обычном конструкторе
	//	AddRef();
}

// Смотри комент к копирующему конструктору
AVRefCounter& AVRefCounter::operator=(const AVRefCounter&)
{
	return *this;
}

void AVRefCounter::AddRef() const
{
	m_ref_count.ref();
};

void AVRefCounter::Release() const
{
	if( m_ref_count.deref() )
		return;

	{
		m_ref_count.ref();
		OnSelfZeroRef();
		m_ref_count.load();
		const_cast<AVRefCounter*>(this)->Uninit();
		if( m_ref_count.deref() )
			return;
	}

	SelfDelete();
};

void AVRefCounter::SelfDelete() const
{
	// Это нужно чтоб AddRef/Release вызванные в деструкторе, не приводили к повторному удалению
	m_ref_count.ref();

	// HEAP[]: Invalid Address specified to RtlValidateHeap
	// Наверное объект был создан не через new (например в стэке или мемберах класса)
	// но при этом был записан в указатель который теперь пытается кго удалить.
	// По нормальному, в умный указатель должны попадать только объекты которые
	// созданные через new/delete так как умный указатель создан для того
	// чтобы контролировать вызов именно эти операторов.
	//
	// Ошибка в том, что такой объект попал в умный указатель, а не в том что
	// умный указатель пытается его удалить.
	delete this;
}

int AVRefCounter::GetRefCount() const
{
	return m_ref_count.load();
}


void AVRefCounter::AfterAssignAddRefRelease(const AVRefCounter* addref, const AVRefCounter* release)
{
	// В случае присвоения самого себе, экземпляр не должен уничтожится. Потому
	// сначала увеличиваем новый экзампляр, и только потом особождаем старый
	if( addref )
		addref->AddRef();
	if( release )
		release->Release();
}

