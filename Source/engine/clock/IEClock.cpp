#define __IE_DLL_EXPORTS__
#include "IEClock.h"

#include "../atom/IEAtom.h"

IE_BEGIN

IEClock::IEClock()
{
	m_clockType = __clock_type_count__;
	m_ended = false;
}

IEClock::~IEClock()
{

}

void IEClock::Initialization()
{

}

IEClockType IEClock::GetClockType()
{
	return m_clockType;
}

void IEClock::AssembClock(IEAtom * atom, IEFunctionClockTick function)
{
	m_attachAtom = atom;
	m_function = function;
}

void IEClock::ClockTick()
{
	(m_attachAtom->*m_function)(this);
}

IE_END