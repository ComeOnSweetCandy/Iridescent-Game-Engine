/***********************************
* name     : IEThingJoint.h
* creater  : cosc
* info     : �������ϵ�thing Ҫ����Χ��Ԫ����������ͬ
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
	virtual void CheckThing(bool active);			//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

private:
	void RereadSelf();								//���¸ı�����״̬

private:
	bool m_round[8];				//��Χ�Ƿ���ͬ���thing
};

IE_END

#endif