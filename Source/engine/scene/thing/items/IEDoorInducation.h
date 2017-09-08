/***********************************
* name     : IEDoorInducation.h
* creater  : cosc
* info     : Induction door
* date     : 2017/8/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DOOR_INDUCTION__
#define __IE_DOOR_INDUCTION__

#include "../IEThingLine.h"

IE_BEGIN

class __IE_DLL__ IEDoorInducation :public IEThingLine
{
public:
	IEDoorInducation();
	virtual ~IEDoorInducation();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEDoorInducation * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);						//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

protected:
	virtual void Live();

private:
	void BindSelfTrigger();										//���ϴ�����
	void TriggerStrike(IEPhysicNode * physicNode);				//�ű�����ʱ��ĺ���

private:
	bool m_switch;												//��ǰ����״̬
	bool m_lastSwitch;											//��һ�ο���״̬
};

IE_END

#endif