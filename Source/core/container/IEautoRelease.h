/***********************************
* name     : IEautoRelease.h
* creater  : cosc
* info     : object auto release
* date     : 2016/11/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_AUTORELEASE__
#define __IE_AUTORELEASE__

#include "../../global/IEstdafx.h"

IE_BEGIN

class __IE_DLL__ IEAutoRelease
{
public:
	virtual void AutoRelease();
};

IE_END

#endif