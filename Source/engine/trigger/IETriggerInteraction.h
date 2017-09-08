/***********************************
* name     : IEinteractionTrigger.h
* creater  : cosc
* info     : trigger interaction
* date     : 2017/2/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TRIGGER_INTERACTION__
#define __IE_TRIGGER_INTERACTION__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IETriggerInteraction :public IETrigger
{
public:
	IETriggerInteraction();
	virtual ~IETriggerInteraction();
	virtual void Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IETriggerInteraction * Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

protected:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif