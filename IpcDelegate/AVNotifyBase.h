#pragma once

#include "LinkedList.h"
#include "AVRefCounter.h"
#include "AVWeakBase.h"
#include "DelegateW.h"


//-------------------------------------------------------
class AVNotifyWeakBase;

class AVDeleteNotifyWeak: public LinkedListElement, public AVRefCounter
{
public:

	struct Handlers
	{
		DelegateW<void(const void* destruction_weak_alive)> OnDestruct;
	};

	AVDeleteNotifyWeak(const Handlers& handlers, const AVNotifyWeakBase* sender);
	AVDeleteNotifyWeak(const AVDeleteNotifyWeak* handlers, const AVNotifyWeakBase* sender);
	~AVDeleteNotifyWeak();

	void Notify_OnDelete(const void* destruction_weak_alive);
	virtual void Notify_OnZeroRef() {};


protected:

	Handlers m_handlers;
};

//-------------------------------------------------------

class AVDeleteNotify: public AVDeleteNotifyWeak
{
public:

	struct Handlers: public AVDeleteNotifyWeak::Handlers
	{
		DelegateW<void()> OnZeroRef;
	};

	AVDeleteNotify(const Handlers& handlers, const AVNotifyWeakBase* sender);
	AVDeleteNotify(const AVDeleteNotify* handlers, const AVNotifyWeakBase* sender);
	~AVDeleteNotify();

	void Notify_OnZeroRef() override;

private:

	struct HandlersDerived
	{
		DelegateW<void()> OnZeroRef;
	};

private:

	HandlersDerived m_handlers;
};

//-------------------------------------------------------

class AVNotifyWeakBase: public AVWeakBase
{
public:


public:
	AVNotifyWeakBase();
	AVNotifyWeakBase(const AVNotifyWeakBase& other);
	~AVNotifyWeakBase();

	void SubscribeDelete(AVDeleteNotifyWeak* handler) const;

protected:
	static void Process_OnSelfZeroRef(LinkedList<AVDeleteNotifyWeak>* notifications);

protected:

	mutable LinkedList<AVDeleteNotifyWeak> m_notifications;
};

//-------------------------------------------------------
