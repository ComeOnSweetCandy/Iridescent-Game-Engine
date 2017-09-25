/***********************************
* name     : IEActionWalk.h
* creater  : cosc
* info     : action displacement
* date     : 2017/7/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_WALK__
#define __IE_ACTION_WALK__

#include "IEAction.h"

IE_BEGIN

class __IE_DLL__ IEActionWalk :public IEAction
{
public:
	IEActionWalk();
	virtual ~IEActionWalk();
	virtual void Initialization(float x, float y);
	virtual void Initialization(int x, int y);
	static IEActionWalk * Create(float x, float y);				//���ݾ���λ��ȥ�趨ֵ
	static IEActionWalk * Create(int x, int y);					//���ݷ���ȥ�趨ֵ

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	void SetActionNodeDisplacement();		//���㵱ǰ�ĳ���
	void SetActionNodeFaceDirection();		//���㵱ǰ�ĳ���ssss

private:
	int m_valueType;				//���ݹ�����ֵ������
	int m_doubleDirection[2];		//���ݵ���ֵΪ����
	int m_singleDirection;			//��ǰ�ķ���
	float m_displace[2];			//���ݵ���ֵΪλ�Ƶľ���
};

IE_END

#endif