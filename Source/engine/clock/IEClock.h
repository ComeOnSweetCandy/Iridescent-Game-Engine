/***********************************
* name     : IEClock.h
* creater  : cosc
* info     : 关键目的在于计数计时 可以反馈给触发者 理论上生物体内部都应该有一个时钟 挂在atom上面
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CLOCK__
#define __IE_CLOCK__

#include "../../core/IEobject.h"

IE_BEGIN

class IEClock;
class IEAtom;

typedef void(IEAtom::*IEFunctionClockTick)(IEClock * self);			//计时器到时间了 应该在回调函数中会自带clock本身 所有atom内无需拿参数去存储

enum __IE_DLL__ IEClockType
{
	__clock_none_type__,			//没有计时器
	__clock_time_type__,			//时间计时器
	__clock_count_type__,			//撞击次数计数器
	__clock_type_count__			//计时器类型计数
};

class __IE_DLL__ IEClock:public IEObject
{
public:
	IEClock();
	virtual ~IEClock();
	virtual void Initialization();

public:
	virtual void Run() = 0;			//正常运行
	virtual void Reset() = 0;		//重置
	virtual void Stir() = 0;		//主动拨钟

	IEClockType GetClockType();
	void AssembClock(IEAtom * atom, IEFunctionClockTick function);
	void ClockTick();

protected:
	bool m_ended;
	IEClockType m_clockType;
	IEAtom * m_attachAtom;
	IEFunctionClockTick m_function;
};

IE_END

#endif