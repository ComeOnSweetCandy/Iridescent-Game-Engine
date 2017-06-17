/***********************************
* name     : IEtime.h
* creater  : cosc
* info     : time tool
* date     : 2016/11/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TIME__
#define __IE_TIME__

#include "../global/IEstdafx.h"

IE_BEGIN

#define __IE_RECKON_TIME_BEGIN__ \
	IETime::Share()->ReckonBegin()

#define __IE_RECKON_TIME_END__ \
	IETime::Share()->ReckonEnd()

class __IE_DLL__ IETime
{
public:
	IETime();
	~IETime();
	virtual void Initialization();
	virtual void Release();
	static IETime * Share();

public:
	void Run();
	float GetLastFrapPassingTime(); 
	float GetFps(unsigned long elapsedFrames = 1);
	void LockFps(unsigned char targetFPS);
	void ReckonBegin();
	float ReckonEnd();

private:
	void CalFrapsSpacing();
	float CalculateTimes(LONGLONG ticks);

private:
	static IETime * m_time;

	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_ticksPerSecond;
	LARGE_INTEGER m_reckonBeginTime;
	unsigned char m_lockFps;
	float m_lockTime;
	float m_lastFrapPassingTime;
};

IE_END

#endif
