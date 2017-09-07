/***********************************
* name     : IEInteraction.h
* creater  : cosc
* info     : Interaction thing
* date     : 2017/4/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INTERACTION__
#define __IE_INTERACTION__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEInteraction :public IEThing
{
public:
	IEInteraction();
	virtual ~IEInteraction();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEInteraction * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckAround(bool active);						//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

protected:
	virtual void Live();

private:
	void BindTriggers();										//���ϴ�����
	void TriggerStrike(IEPhysicNode * physicNode);				//�ű�����ʱ��ĺ���

	void RereadSelf();											//���¸ı�����״̬

private:
	bool m_switch;												//��ǰ����״̬

	bool m_round[4];											//���ܵ�ռ��
};

IE_END

#endif