#pragma once

#include "AVPreprocessorRepeatJoin.h"
#include "AVInternal_NS.h"
#include "SOW.h"

template<typename TCls>
class SOC: public AVRefCounter, public TCls
{
public:

	SOC()
	{
	}

#define AV_CLS SOC
#define AV_T_BASE TCls
#define AV_NUM_ARGS 1
#include "SO_N.h"
#define AV_NUM_ARGS 2
#include "SO_N.h"
#define AV_NUM_ARGS 3
#include "SO_N.h"
#define AV_NUM_ARGS 4
#include "SO_N.h"
#define AV_NUM_ARGS 5
#include "SO_N.h"
#define AV_NUM_ARGS 6
#include "SO_N.h"
#define AV_NUM_ARGS 7
#include "SO_N.h"
#define AV_NUM_ARGS 8
#include "SO_N.h"
#undef AV_CLS
#undef AV_T_BASE

};

//-------------------------------------------------------


template<typename TCls>
class SOExtend_Simple: public SOC<SOW<TCls> >
{
private:
	typedef SOC<SOW<TCls> > TBase;

public:

	SOExtend_Simple()
	{
	}

#define AV_CLS SOExtend_Simple
#define AV_T_BASE TBase
#define AV_NUM_ARGS 1
#include "SO_N.h"
#define AV_NUM_ARGS 2
#include "SO_N.h"
#define AV_NUM_ARGS 3
#include "SO_N.h"
#define AV_NUM_ARGS 4
#include "SO_N.h"
#define AV_NUM_ARGS 5
#include "SO_N.h"
#define AV_NUM_ARGS 6
#include "SO_N.h"
#define AV_NUM_ARGS 7
#include "SO_N.h"
#define AV_NUM_ARGS 8
#include "SO_N.h"
#undef AV_CLS
#undef AV_T_BASE

protected:

	void OnSelfZeroRef() const override
	{
		AVNotifyWeakBase::Process_OnSelfZeroRef(&this->m_notifications);
	}

};


template<typename TCls>
class SOExtend_Weak: public AVRefCounter, public TCls
{
public:

	SOExtend_Weak()
	{
	}

#define AV_CLS SOExtend_Weak
#define AV_T_BASE TCls
#define AV_NUM_ARGS 1
#include "SO_N.h"
#define AV_NUM_ARGS 2
#include "SO_N.h"
#define AV_NUM_ARGS 3
#include "SO_N.h"
#define AV_NUM_ARGS 4
#include "SO_N.h"
#define AV_NUM_ARGS 5
#include "SO_N.h"
#define AV_NUM_ARGS 6
#include "SO_N.h"
#define AV_NUM_ARGS 7
#include "SO_N.h"
#define AV_NUM_ARGS 8
#include "SO_N.h"
#undef AV_CLS
#undef AV_T_BASE


protected:

	void OnSelfZeroRef() const override
	{
		AVNotifyWeakBase::Process_OnSelfZeroRef(&this->m_notifications);
	}

};

//-------------------------------------------------------


template<typename TCls>
class SO: public AVInternal_NS::IsBaseOf<TCls, AVBaseWeak, SOExtend_Weak<TCls>, SOExtend_Simple<TCls> >::ResType
{
	typedef typename AVInternal_NS::IsBaseOf<TCls, AVBaseWeak, SOExtend_Weak<TCls>, SOExtend_Simple<TCls> >::ResType TBase;

public:

	SO()
	{
	}

#define AV_CLS SO
#define AV_T_BASE TBase
#define AV_NUM_ARGS 1
#include "SO_N.h"
#define AV_NUM_ARGS 2
#include "SO_N.h"
#define AV_NUM_ARGS 3
#include "SO_N.h"
#define AV_NUM_ARGS 4
#include "SO_N.h"
#define AV_NUM_ARGS 5
#include "SO_N.h"
#define AV_NUM_ARGS 6
#include "SO_N.h"
#define AV_NUM_ARGS 7
#include "SO_N.h"
#define AV_NUM_ARGS 8
#include "SO_N.h"
#undef AV_CLS
#undef AV_T_BASE

protected:

	~SO()
	{
	}

};
