/***********************************
* name     : IEThingCreator.h
* creater  : cosc
* info     : thing´´½¨Æ÷
* date     : 2017/9/1
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_CREATOR__
#define __IE_THING_CREATOR__

#include "IEThing.h"

IE_BEGIN

extern "C" __IE_DLL__ IEThing * CreateThing(unsigned int thingID, unsigned int thingOrder);
extern "C" __IE_DLL__ IEThing * CreateThingByType(unsigned int thingID, unsigned int thingOrder);

IE_END

#endif