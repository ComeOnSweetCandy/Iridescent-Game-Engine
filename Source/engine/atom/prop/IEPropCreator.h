/***********************************
* name     : IEPropCreator.h
* creater  : cosc
* info     : thing´´½¨Æ÷
* date     : 2017/9/1
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_CREATOR__
#define __IE_PROP_CREATOR__

#include "IEProp.h"

IE_BEGIN

extern "C" __IE_DLL__ IEProp * CreateProp(unsigned int propID, IEPropState propState);

IE_END

#endif