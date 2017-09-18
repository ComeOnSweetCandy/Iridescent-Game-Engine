/***********************************
* name     : IEThingJoint.h
* creater  : cosc
* info     : 可以联合的thing 要求周围的元素与自身相同
* date     : 2017/6/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_JOINT__
#define __IE_THING_JOINT__

#include "IEThing.h"

IE_BEGIN

class __IE_DLL__ IEThingJoint :public IEThing
{
public:
	IEThingJoint();
	virtual ~IEThingJoint();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEThingJoint * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);			//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

private:
	void RereadSelf();								//重新改变自身状态

private:
	bool m_round[8];				//周围是否有同类的thing
};

IE_END

#endif