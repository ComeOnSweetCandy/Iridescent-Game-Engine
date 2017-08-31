/***********************************
* name     : IEDoor.h
* creater  : cosc
* info     : special thing door
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
	virtual void Initialization(unsigned int thingID);
	static IEDoor * Create(unsigned int thingID);

protected:
	virtual void Update();

	virtual void ChangeState(unsigned int stateIndex);

private:

};

IE_END

#endif