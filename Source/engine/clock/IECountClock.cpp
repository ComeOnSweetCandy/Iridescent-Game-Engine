#define __IE_DLL_EXPORTS__
#include "IECountClock.h"

IE_BEGIN

IECountClock::IECountClock()
{
	m_clockType = __clock_count_type__;

	m_maxCount = 0;
	m_curCount = 0;
}

IECountClock::~IECountClock()
{

}

void IECountClock::Initialization(int maxCount)
{
	m_maxCount = maxCount;
}

IECountClock * IECountClock::Create(int maxCount)
{
	IECountClock * clock = new IECountClock();
	clock->Initialization(maxCount);
	return clock;
}

void IECountClock::Run()
{
	if (m_ended)
	{
		return;
	}

	if (m_curCount >= m_maxCount)
	{
		m_ended = true;
		ClockTick();
	}
}

void IECountClock::Stir()
{
	m_curCount++;
}

void IECountClock::Reset()
{
	m_curCount = 0;
	m_ended = false;
}

IE_END