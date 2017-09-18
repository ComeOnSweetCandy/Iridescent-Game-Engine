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
	static IEDisplacement * Create(float x, float y);				//根据具体位移去设定值
	static IEDisplacement * Create(int x, int y);					//根据方向去设定值

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