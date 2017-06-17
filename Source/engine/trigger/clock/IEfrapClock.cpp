#define __IE_DLL_EXPORTS__
#include "IEfrapClock.h"

IE_BEGIN

IEFrapClock::IEFrapClock()
{
	m_clockType = __clock_time_type__;

	m_topTimes = 0;
	m_curTimes = 0;
}

IEFrapClock::~IEFrapClock()
{

}

void IEFrapClock::Initialization(int topTimes)
{
	m_topTimes = topTimes;
}

IEFrapClock * IEFrapClock::Create(int topTimes)
{
	IEFrapClock * clock = new IEFrapClock();
	clock->Initialization(topTimes);
	return clock;
}

void IEFrapClock::Run()
{
	if (m_end)
	{
		return;
	}

	m_curTimes++;
	if (m_topTimes>0 && m_curTimes >= m_topTimes)
	{
		m_end = true;
	}
}

IE_END