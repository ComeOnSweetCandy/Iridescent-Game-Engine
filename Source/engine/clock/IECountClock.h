/***********************************
* name     : IECountClock.h
* creater  : cosc
* info     : 计数clock
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_COUNT_CLOCK__
#define __IE_COUNT_CLOCK__

#include "IEclock.h"

IE_BEGIN

class __IE_DLL__ IECountClock :public IEClock
{
public:
	IECountClock();
	virtual ~IECountClock();
	virtual void Initialization(int topTimes);
	static IECountClock * Create(int topTimes);

public:
	virtual void Run();					//正常运行
	virtual void Stir();				//主动拨钟不采取任何行动
	virtual void Reset();				//重置时间为0

private:
	int m_maxCount;
	int m_curCount;
};

IE_END

#endif