/***********************************
* name     : IECycleThing.h
* creater  : cosc
* info     : һ������������������thing
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
	virtual void CheckThing(bool active);						//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

protected:
	virtual void Live();

private:
	void BindClock();											//���ϼ�ʱ��
	void TriggerStrike(IEPhysicNode * physicNode);				//�ű�����ʱ��ĺ���

private:
	
};

IE_END

#endif