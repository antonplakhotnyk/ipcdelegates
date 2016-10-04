#include "stdafx.h"
#include "AVWeakBase.h"


AVWeakBase::AVWeakBase()
{
}

AVWeakBase::~AVWeakBase()
{
	if( m_shared )
		m_shared->Clear();
}

WPtrShared_NS::Shared* AVWeakBase::GetWeakShared() const
{
	return m_shared;
}

void AVWeakBase::SetWeakShared(WPtrShared_NS::Shared* shared) const
{
	m_shared = shared;
}
