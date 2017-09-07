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
	virtual void CheckAround(bool active);						//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

protected:
	virtual void Live();

private:
	void BindTriggers();										//绑定上触发器
	void TriggerStrike(IEPhysicNode * physicNode);				//门被触发时候的函数

	void RereadSelf();											//重新改变自身状态

private:
	bool m_switch;												//当前开关状态

	bool m_round[4];											//四周的占点
};

IE_END

#endif