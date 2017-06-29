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

#include "IEthing.h"

IE_BEGIN

class __IE_DLL__ IEJoint :public IEThing
{
public:
	IEJoint();
	virtual ~IEJoint();
	virtual void Initialization(unsigned int thingID);
	static IEJoint * Create(unsigned int thingID);

public:
	//�趨��Χ��thing
	void SetRound(unsigned char roundIndex ,unsigned int thingID);

protected:
	virtual void DrawNode();

private:
	//��ʼ��ͷ����sprite
	void BuildTopSprite(unsigned int thingID);

private:
	unsigned char m_topHeight;		//���Ƶĸ߶�����
	bool m_round[4];				//��Χ�Ƿ���ͬ���thing
	IESprite * m_topBackground;		//�����ĵ�Ƭ
	IESprite * m_topBorder[4];		//�����ı�
};

IE_END

#endif