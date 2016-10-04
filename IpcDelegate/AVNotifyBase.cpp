#include "stdafx.h"
#include "AVNotifyBase.h"

//-------------------------------------------------------
AVDeleteNotifyWeak::~AVDeleteNotifyWeak()
{
}

AVDeleteNotifyWeak::AVDeleteNotifyWeak(const Handlers& handlers, const AVNotifyWeakBase* sender)
	:m_handlers(handlers)
{
	if( sender )
		sender->SubscribeDelete(this);
}

AVDeleteNotifyWeak::AVDeleteNotifyWeak(const AVDeleteNotifyWeak* handlers, const AVNotifyWeakBase* sender)
{
	if( handlers )
		m_handlers = handlers->m_handlers;
	if( sender )
		sender->SubscribeDelete(this);
}


void AVDeleteNotifyWeak::Notify_OnDelete(const void* destruction_weak_alive)
{
	m_handlers.OnDestruct(destruction_weak_alive);
}

//-------------------------------------------------------

AVNotifyWeakBase::AVNotifyWeakBase()
{
}

// В принципе эту штуку можно копировать, но копия, это уже другой экземпляр, 
// с другими нотификациями
AVNotifyWeakBase::AVNotifyWeakBase(const AVNotifyWeakBase& other)
{
}

AVNotifyWeakBase::~AVNotifyWeakBase()
{
	LinkedList<AVDeleteNotifyWeak> tmp_head;
	m_notifications.MoveToList(&tmp_head);
	while(true)
	{
		OPtr<AVDeleteNotifyWeak> life_time_call_it = tmp_head.Front();
		if( !life_time_call_it )
			break;
		life_time_call_it->RemoveFromList();
		m_notifications.PushBack(life_time_call_it);

		life_time_call_it->Notify_OnDelete(this);
	}
}

void AVNotifyWeakBase::SubscribeDelete(AVDeleteNotifyWeak* handler) const
{
	m_notifications.PushBack(handler);
}

void AVNotifyWeakBase::Process_OnSelfZeroRef(LinkedList<AVDeleteNotifyWeak>* notifications)
{
	LinkedList<AVDeleteNotifyWeak> tmp_head;
	notifications->MoveToList(&tmp_head);
	while( true )
	{
		OPtr<AVDeleteNotifyWeak> life_time_call_it = tmp_head.Front();
		if( !life_time_call_it )
			break;
		life_time_call_it->RemoveFromList();
		notifications->PushBack(life_time_call_it);

		life_time_call_it->Notify_OnZeroRef();
	}
}


//-------------------------------------------------------
AVDeleteNotify::~AVDeleteNotify()
{
}

void AVDeleteNotify::Notify_OnZeroRef()
{
	m_handlers.OnZeroRef();
}

AVDeleteNotify::AVDeleteNotify(const Handlers& handlers, const AVNotifyWeakBase* sender)
	:AVDeleteNotifyWeak(handlers, sender)
	, m_handlers({handlers.OnZeroRef})
{
}

AVDeleteNotify::AVDeleteNotify(const AVDeleteNotify* handlers, const AVNotifyWeakBase* sender)
	: AVDeleteNotifyWeak(handlers, sender)
{
	if( handlers )
		m_handlers.OnZeroRef = handlers->m_handlers.OnZeroRef;
}

//-------------------------------------------------------
