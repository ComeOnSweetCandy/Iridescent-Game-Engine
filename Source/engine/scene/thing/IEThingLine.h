/***********************************
* name     : IEThingLine.h
* creater  : cosc
* info     : �������ϵ�thing ����ֻ�ܺ�һ�������ϵ���ͬԪ������
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
	virtual void CheckThing(bool active);			//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

private:
	void RereadSelf();								//���¸ı�����״̬

private:
	bool m_round[4];				//��Χ�Ƿ���ͬ���thing
};

IE_END

#endif