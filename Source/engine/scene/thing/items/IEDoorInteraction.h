/***********************************
* name     : IEDoorInteraction.h
* creater  : cosc
* info     : ��Ҫ�ֶ������� ������thing
* date     : 2017/4/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DOOR_INTERACTION__
#define __IE_DOOR_INTERACTION__

#include "../IEThingLine.h"

IE_BEGIN

class __IE_DLL__ IEDoorInteraction :public IEThingLine
{
public:
	IEDoorInteraction();
	virtual ~IEDoorInteraction();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEDoorInteraction * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);						//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

protected:
	virtual void Live();

private:
	void BindTriggers();										//���ϴ�����
	void TriggerStrike(IEPhysicNode * physicNode);				//�ű�����ʱ��ĺ���

private:
	bool m_switch;												//��ǰ����״̬
};

IE_END

#endif