/***********************************
* name     : IEThingLine.h
* creater  : cosc
* info     : 可以联合的thing 但是只能和一条横线上的相同元素联合
* date     : 2017/6/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_LINE__
#define __IE_THING_LINE__

#include "IEThing.h"

IE_BEGIN

class __IE_DLL__ IEThingLine :public IEThing
{
public:
	IEThingLine();
	virtual ~IEThingLine();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEThingLine * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);			//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

private:
	void RereadSelf();								//重新改变自身状态

private:
	bool m_round[4];				//周围是否有同类的thing
};

IE_END

#endif