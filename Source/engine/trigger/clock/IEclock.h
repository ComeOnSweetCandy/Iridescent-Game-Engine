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
	__clock_none_type__,			//没有计时器
	__clock_time_type__,			//时间计时器
	__clock_strike_times_type__,	//撞击次数计数器
	__clock_type_count__			//计时器类型计数
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