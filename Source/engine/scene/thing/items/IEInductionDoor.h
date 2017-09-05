/***********************************
* name     : IEInductionDoor.h
* creater  : cosc
* info     : Induction door
* date     : 2017/8/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INDUCTION_DOOR__
#define __IE_INDUCTION_DOOR__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEInductionDoor :public IEThing
{
public:
	IEInductionDoor();
	virtual ~IEInductionDoor();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEInductionDoor * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckAround(bool active);		//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

protected:
	virtual void Live();

private:
	void RereadSelf();											//���¸ı�����״̬
	void BindTriggers();										//���ϴ�����
	void TriggerStrike(IEPhysicNode * physicNode);				//�ű�����ʱ��ĺ���

private:
	bool m_switch;
	bool m_round[4];											//���ܵ�ռ��
};

IE_END

#endif