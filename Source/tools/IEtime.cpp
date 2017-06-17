#define __IE_DLL_EXPORTS__
#include "IEtime.h"

IE_BEGIN

IETime *IETime::m_time = NULL;

IETime::IETime()
{ 

}

IETime::~IETime()
{

}

IETime * IETime::Share()
{
	if (m_time == NULL)
	{
		m_time = new IETime();
		m_time->Initialization();
	}
	return m_time;
}

void IETime::Release()
{
	delete this;
}

void IETime::Initialization()
{
	LockFps(60);

	if (!QueryPerformanceFrequency(&m_ticksPerSecond))
	{
		__IE_WARNING__("ietime init error\n");
	}
	else
	{
		QueryPerformanceCounter(&m_startTime);
	}
}

void IETime::Run()
{
	static LARGE_INTEGER s_LastTime = m_startTime;
	LARGE_INTEGER curreIETime;
	float fps;
	do
	{
		QueryPerformanceCounter(&curreIETime);
		fps = (float)m_ticksPerSecond.QuadPart / ((float)(curreIETime.QuadPart - s_LastTime.QuadPart));

	} while (fps > (float)m_lockFps);
	s_LastTime = curreIETime;

	this->CalFrapsSpacing();
}

float IETime::GetLastFrapPassingTime()
{
	return m_lastFrapPassingTime;
}

float IETime::CalculateTimes(LONGLONG ticks)
{
	float seconds = (float)(ticks) / ((float)(m_ticksPerSecond.QuadPart));
	return seconds;
}

void IETime::CalFrapsSpacing()
{
	static LARGE_INTEGER s_LastTime = m_startTime;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);
	float seconds = (float)(currentTime.QuadPart - s_LastTime.QuadPart) / ((float)(m_ticksPerSecond.QuadPart));
	
	s_LastTime = currentTime;
	m_lastFrapPassingTime =  seconds;
	m_lastFrapPassingTime > m_lockTime ? m_lastFrapPassingTime = m_lockTime : m_lastFrapPassingTime;
}

float IETime::GetFps(unsigned long elapsedFrames)
{
	static LARGE_INTEGER s_LastTime = m_startTime;
	LARGE_INTEGER currentTime;
	QueryPerformanceFrequency(&currentTime);
	float fps = (float)elapsedFrames * (float)m_ticksPerSecond.QuadPart / ((float)currentTime.QuadPart - (float)s_LastTime.QuadPart);
	s_LastTime = currentTime;
	return fps;
}

void IETime::LockFps(unsigned char targetFPS)
{
	m_lockFps = targetFPS > 1 ? targetFPS : 1;
	m_lockTime = 1.0f / m_lockFps;
}

void IETime::ReckonBegin()
{
	QueryPerformanceCounter(&m_reckonBeginTime);
}

float IETime::ReckonEnd()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	float spentTime = CalculateTimes(currentTime.QuadPart - m_reckonBeginTime.QuadPart);
	return spentTime;
}

IE_END
