/***********************************
* name     : IEDisplacement.h
* creater  : cosc
* info     : action displacement
* date     : 2017/7/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DISPLACEMENT__
#define __IE_DISPLACEMENT__

#include "IEAction.h"

IE_BEGIN

class __IE_DLL__ IEDisplacement :public IEAction
{
public:
	IEDisplacement();
	virtual ~IEDisplacement();
	virtual void Initialization(float x, float y);
	virtual void Initialization(int x, int y);
	static IEDisplacement * Create(float x, float y);
	static IEDisplacement * Create(int x, int y);

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	void SetActionNodeDisplacement();
	void SetActionNodeFaceDirection();

private:
	IEVector m_displacement;

	int m_valueType;				//���ݹ�����ֵ������
	int m_direction[2];				//���ݵ���ֵΪ����
	//float m_displacement[2];		//����������ֵΪ
};

IE_END

#endif