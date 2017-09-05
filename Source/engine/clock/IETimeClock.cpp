#define __IE_DLL_EXPORTS__
#include "IETimeClock.h"

#include "../../tools/IEtime.h"

IE_BEGIN

IETimeClock::IETimeClock()
{
	m_clockType = __clock_time_type__;

	m_maxTime = 0.0f;
	m_curTime = 0.0f;
}

IETimeClock::~IETimeClock()
{

}

void IETimeClock::Initialization(float maxTime)
{
	m_maxTime = maxTime;
}

IETimeClock * IETimeClock::Create(float maxTime)
{
	IETimeClock * clock = new IETimeClock();
	clock->Initialization(maxTime);
	return clock;
}

void IETimeClock::Run()
{
	if (m_ended)
	{
		return;
	}

	m_curTime = m_curTime + IETime::Share()->GetLastFrapPassingTime();
	if (m_curTime >= m_maxTime)
	{
		m_ended = true;
		ClockTick();
	}
}

void IETimeClock::Stir()
{
	//do nothing
}

void IETimeClock::Reset()
{
	m_curTime = 0.0f;
	m_ended = false;
}

IE_END