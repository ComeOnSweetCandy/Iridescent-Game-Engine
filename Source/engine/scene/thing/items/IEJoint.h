/***********************************
* name     : IEJoint.h
* creater  : cosc
* info     : 可以联合的thing
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
	virtual void CallFinal();

protected:
	void CheckAround();							//根据四周元素测算的同时，四周元素自身也进行计算。
	void RereadSelf();

private:
	//初始化头顶的sprite
	void BuildTopSprite(unsigned int thingID);

private:
	unsigned char m_topHeight;		//绘制的高度问题
	bool m_round[4];				//周围是否有同类的thing
	IESprite * m_topBackground;		//顶部的底片
	IESprite * m_topBorder[4];		//顶部的边
};

IE_END

#endif