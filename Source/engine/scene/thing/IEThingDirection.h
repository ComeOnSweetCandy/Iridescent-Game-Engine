/***********************************
* name     : IEThingDirection.h
* creater  : cosc
* info     : ���з���Ķ���thing
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
	virtual void CheckThing(bool active);			//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣
};

IE_END

#endif