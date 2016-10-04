#pragma once

#include "DelegateW.h"

template<typename TDelProc, template<class> class TStorePtr = WPtr>
class FunctgateW: public DelegateW<TDelProc, TStorePtr>
{
private:

	using DelegateW<TDelProc, TStorePtr>::BindE;
	using DelegateW<TDelProc, TStorePtr>::BindES;
	using DelegateW<TDelProc, TStorePtr>::BindED;
	using DelegateW<TDelProc, TStorePtr>::BindEAdd;
	using DelegateW<TDelProc, TStorePtr>::BindESAdd;
	using DelegateW<TDelProc, TStorePtr>::BindEDAdd;
	using DelegateW<TDelProc, TStorePtr>::operator +=;
	using DelegateW<TDelProc, TStorePtr>::operator =;

public:

// 	// Этот класс предотвращает случайный прямой бинд но
// 	// не позволяет скопировать в него уже забиндженный прямой DelegateW 
// 	EventgateRC<TDelProc>& operator= (const DelegateW<TDelProc>& val)
// 	{
// 		DelegateW<TDelProc>::operator=(val);
// 		return *this;
// 	}

};