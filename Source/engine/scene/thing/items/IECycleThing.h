/***********************************
* name     : IECycleThing.h
* creater  : cosc
* info     : 一种周期性主动触发的thing
* date     : 2017/9/12
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CYCLE_THING__
#define __IE_CYCLE_THING__

#include "../IEThingLine.h"

#include "../../../clock/IEClock.h"

IE_BEGIN

class __IE_DLL__ IECycleThing :public IEThingLine
{
public:
	IECycleThing();
	virtual ~IECycleThing();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IECycleThing * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);						//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

protected:
	virtual void Live();

private:
	void BindClock();											//绑定上计时器
	void TriggerStrike(IEPhysicNode * physicNode);				//门被触发时候的函数

private:
	
};

IE_END

#endif