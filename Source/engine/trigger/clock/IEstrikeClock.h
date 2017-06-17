/***********************************
* name     : IEstrikeClock.h
* creater  : cosc
* info     : clock frap
* c_date   : 2017/3/27
* l_date   : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_STRIKE_CLOCK__
#define __IE_STRIKE_CLOCK__

#include "IEclock.h"

IE_BEGIN

class __IE_DLL__ IEStrikeClock :public IEClock
{
public:
	IEStrikeClock();
	virtual ~IEStrikeClock();
	virtual void Initialization(int topTimes);
	static IEStrikeClock * Create(int topTimes);

public:
	virtual void Run();
	virtual void TriggerStrike();

private:
	int m_topTimes;
	int m_curTimes;
};

IE_END

#endif