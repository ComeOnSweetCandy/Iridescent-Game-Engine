/***********************************
* name     : IEJoint.h
* creater  : cosc
* info     : �������ϵ�thing
* date     : 2017/6/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_JOINT__
#define __IE_JOINT__

#include "../IEThing.h"

IE_BEGIN

class __IE_DLL__ IEJoint :public IEThing
{
public:
	IEJoint();
	virtual ~IEJoint();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEJoint * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckAround(bool active);			//���� �Ƿ�Ϊ�Է��� ��������Ԫ�ز����ͬʱ������Ԫ������Ҳ���м��㡣

private:
	void RereadSelf();								//���¸ı�����״̬
	void BuildTopSprite(unsigned int thingID);		//��ʼ��ͷ����sprite

private:
	unsigned char m_topHeight;		//���Ƶĸ߶�����
	bool m_round[4];				//��Χ�Ƿ���ͬ���thing
	IESprite * m_topBackground;		//�����ĵ�Ƭ
	IESprite * m_topBorder[4];		//�����ı�
};

IE_END

#endif