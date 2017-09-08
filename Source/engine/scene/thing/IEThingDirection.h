/***********************************
* name     : IEThingDirection.h
* creater  : cosc
* info     : 具有方向的独立thing
* date     : 2017/9/8
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_DIRECTION__
#define __IE_THING_DIRECTION__

#include "IEThing.h"

IE_BEGIN

class __IE_DLL__ IEThingDirection :public IEThing
{
public:
	IEThingDirection();
	virtual ~IEThingDirection();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEThingDirection * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);			//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。
};

IE_END

#endif