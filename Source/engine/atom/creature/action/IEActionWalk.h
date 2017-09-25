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
	static IEActionWalk * Create(float x, float y);				//根据具体位移去设定值
	static IEActionWalk * Create(int x, int y);					//根据方向去设定值

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	void SetActionNodeDisplacement();		//计算当前的朝向
	void SetActionNodeFaceDirection();		//计算当前的朝向ssss

private:
	int m_valueType;				//传递过来的值的类型
	int m_doubleDirection[2];		//传递的数值为方向
	int m_singleDirection;			//当前的方向
	float m_displace[2];			//传递的数值为位移的距离
};

IE_END

#endif