/***********************************
* name     : IEInductionDoor.h
* creater  : cosc
* info     : Induction door
* date     : 2017/8/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INDUCTION_DOOR__
#define __IE_INDUCTION_DOOR__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEInductionDoor :public IEThing
{
public:
	IEInductionDoor();
	virtual ~IEInductionDoor();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEInductionDoor * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckAround(bool active);		//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

protected:
	virtual void Live();

private:
	void RereadSelf();											//重新改变自身状态
	void BindTriggers();										//绑定上触发器
	void TriggerStrike(IEPhysicNode * physicNode);				//门被触发时候的函数

private:
	bool m_switch;
	bool m_round[4];											//四周的占点
};

IE_END

#endif