/***********************************
* name     : IEClockCreator.h
* creater  : cosc
* info     : clock´´½¨Æ÷
* date     : 2017/9/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CLOCK_CREATOR__
#define __IE_CLOCK_CREATOR__

#include "IEclock.h"

IE_BEGIN

extern "C" __IE_DLL__ IEClock * CreateClock(IEClockType clockType, int param);
extern "C" __IE_DLL__ IEClock * CreateClockByType(IEClockType clockType, int param);

IE_END

#endif