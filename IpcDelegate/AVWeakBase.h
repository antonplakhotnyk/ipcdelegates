#pragma once

#include "AVRefCounter.h"
#include "OPtr.h"

class AVWeakBase;
         
namespace WPtrShared_NS
{

class Shared: public AVRefCounter
{
private:
	friend class ::AVWeakBase;

	virtual void Clear(){};
};

class AVWeakBasePrivate
{
protected:
	mutable OPtr<WPtrShared_NS::Shared> m_shared;
};

template<typename TDerived>
struct SharedSpecific: public Shared
{
private:
	TDerived* m_alive;

public:
	SharedSpecific(TDerived* alive):m_alive(alive){};

	TDerived* Get()
	{
		return m_alive;
	}

private:

	void Clear() override
	{
		m_alive = NULL;
	}

};


template<class T>
T* RefCounterPtrAssign(OPtr<WPtrShared_NS::SharedSpecific<T> >* this_p, T* lp);
};


//-------------------------------------------------------


class AVWeakBase: private WPtrShared_NS::AVWeakBasePrivate
{
public:

	AVWeakBase();
	~AVWeakBase();

private:

	template<class T>
	friend T* WPtrShared_NS::RefCounterPtrAssign(OPtr<WPtrShared_NS::SharedSpecific<T> >* this_p, T* lp);


	void					SetWeakShared(WPtrShared_NS::Shared* shared) const;
	WPtrShared_NS::Shared*	GetWeakShared() const;

};

