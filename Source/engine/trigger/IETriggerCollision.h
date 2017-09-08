/***********************************
* name     : IEcollisionTrigger.h
* creater  : cosc
* info     : trigger collision
* date	   : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_COLLISION_TRIGGER__
#define __IE_COLLISION_TRIGGER__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IETriggerCollision :public IETrigger
{
public:
	IETriggerCollision();
	virtual ~IETriggerCollision();
	virtual void Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IETriggerCollision * Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif