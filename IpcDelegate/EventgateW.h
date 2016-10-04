#pragma once

#include "DelegateW.h"

template<typename TDelProc, template<class> class TStorePtr = WPtr>
class EventgateW: public DelegateW<TDelProc, TStorePtr>
{
private:

	using DelegateW<TDelProc, TStorePtr>::Bind;
	using DelegateW<TDelProc, TStorePtr>::BindS;
	using DelegateW<TDelProc, TStorePtr>::BindD;
	using DelegateW<TDelProc, TStorePtr>::BindAdd;
	using DelegateW<TDelProc, TStorePtr>::BindSAdd;
	using DelegateW<TDelProc, TStorePtr>::BindDAdd;
	using DelegateW<TDelProc, TStorePtr>::operator +=;
// 	using DelegateW<TDelProc, TStorePtr>::operator =;

public:

// 	// Этот класс предотвращает случайный прямой бинд но
// 	// не позволяет скопировать в него уже забиндженный прямой DelegateW 
	EventgateW<TDelProc>& operator= (const EventgateW<TDelProc>& val)
	{
		DelegateW<TDelProc>::operator=(val);
		return *this;
	}

};