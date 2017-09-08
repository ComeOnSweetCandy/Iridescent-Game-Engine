/***********************************
* name     : IEDoorInducation.h
* creater  : cosc
* info     : Induction door
* date     : 2017/8/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DOOR_INDUCTION__
#define __IE_DOOR_INDUCTION__

#include "../IEThingLine.h"

IE_BEGIN

class __IE_DLL__ IEDoorInducation :public IEThingLine
{
public:
	IEDoorInducation();
	virtual ~IEDoorInducation();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEDoorInducation * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void CheckThing(bool active);						//重载 是否为自发性 根据四周元素测算的同时，四周元素自身也进行计算。

protected:
	virtual void Live();

private:
	void BindSelfTrigger();										//绑定上触发器
	void TriggerStrike(IEPhysicNode * physicNode);				//门被触发时候的函数

private:
	bool m_switch;												//当前开关状态
	bool m_lastSwitch;											//上一次开关状态
};

IE_END

#endif