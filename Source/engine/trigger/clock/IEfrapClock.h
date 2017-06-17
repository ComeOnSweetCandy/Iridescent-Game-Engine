/***********************************
* name     : IEfrapClock.h
* creater  : cosc
* info     : clock frap
* c_date   : 2017/3/23
* l_date   : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FRAP_CLOCK__
#define __IE_FRAP_CLOCK__

#include "IEclock.h"

IE_BEGIN

class __IE_DLL__ IEFrapClock:public IEClock
{
public:
	IEFrapClock();
	virtual ~IEFrapClock();
	virtual void Initialization(int topTimes);
	static IEFrapClock * Create(int topTimes);

public:
	virtual void Run();

private:
	int m_topTimes;
	int m_curTimes;
};

IE_END

#endif