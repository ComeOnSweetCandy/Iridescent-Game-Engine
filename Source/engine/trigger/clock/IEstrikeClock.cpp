#define __IE_DLL_EXPORTS__
#include "IEstrikeClock.h"

IE_BEGIN

IEStrikeClock::IEStrikeClock()
{
	m_clockType = __clock_strike_times_type__;

	m_topTimes = 0;
	m_curTimes = 0;
}

IEStrikeClock::~IEStrikeClock()
{

}

void IEStrikeClock::Initialization(int topTimes)
{
	m_topTimes = topTimes;
}

IEStrikeClock * IEStrikeClock::Create(int topTimes)
{
	IEStrikeClock * clock = new IEStrikeClock();
	clock->Initialization(topTimes);
	return clock;
}

void IEStrikeClock::Run()
{

}

void IEStrikeClock::TriggerStrike()
{
	if (m_end)
	{
		return;
	}

	m_curTimes++;
	if (m_curTimes >= m_topTimes)
	{
		m_end = true;
	}
}

IE_END