#define __IE_DLL_EXPORTS__
#include "IEclock.h"

IE_BEGIN

IEClock::IEClock()
{
	m_clockType = __clock_type_count__;
	m_end = false;
}

IEClock::~IEClock()
{

}

void IEClock::Initialization()
{

}

bool IEClock::IsEnd()
{
	return m_end;
}

void IEClock::SetEnd()
{
	m_end = true;
}

IEClockType IEClock::GetClockType()
{
	return m_clockType;
}

void IEClock::TriggerStrike()
{

}

IE_END