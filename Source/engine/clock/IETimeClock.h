/***********************************
* name     : IETimeClock.h
* creater  : cosc
* info     : 用作倒计时的时钟
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TIME_CLOCK__
#define __IE_TIME_CLOCK__

#include "IEClock.h"

IE_BEGIN

class __IE_DLL__ IETimeClock:public IEClock
{
public:
	IETimeClock();
	virtual ~IETimeClock();
	virtual void Initialization(float maxTime);
	static IETimeClock * Create(float maxTime);

public:
	virtual void Run();					//正常运行
	virtual void Stir();				//主动拨钟不采取任何行动
	virtual void Reset();				//重置时间为0

private:
	float m_maxTime;
	float m_curTime;
};

IE_END

#endif