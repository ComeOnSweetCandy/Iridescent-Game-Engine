/***********************************
* name     : IEDoor.h
* creater  : cosc
* info     : Induction door
* date     : 2017/8/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DOOR__
#define __IE_DOOR__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEDoor :public IEThing
{
public:
	IEDoor();
	virtual ~IEDoor();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEDoor * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	virtual void Live();
	virtual void CallFinal();

	virtual void TriggerStrike(IEPhysicNode * physicNode);		//门被触发时候的函数

protected:
	void CheckAround();

private:
	bool m_switch;
};

IE_END

#endif