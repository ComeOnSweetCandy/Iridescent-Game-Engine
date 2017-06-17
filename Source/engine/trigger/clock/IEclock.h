/***********************************
* name     : IEclock.h
* creater  : cosc
* info     : clock
* c_date   : 2017/3/23
* l_date   : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CLOCK__
#define __IE_CLOCK__

#include "../../../global/IEstdafx.h"

IE_BEGIN

enum __IE_DLL__ IEClockType
{
	__clock_time_type__,
	__clock_strike_times_type__,
	__clock_type_count__
};

class __IE_DLL__ IEClock
{
public:
	IEClock();
	virtual ~IEClock();
	virtual void Initialization();
	static IEClock * Create();

public:
	virtual void Run() = 0;
	virtual bool IsEnd();
	virtual void SetEnd();

	virtual void TriggerStrike();
	IEClockType GetClockType();

protected:
	bool m_end;
	IEClockType m_clockType;
};

IE_END

#endif