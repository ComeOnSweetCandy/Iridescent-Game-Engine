/***********************************
* name     : IEActionAngry.h
* creater  : cosc
* info     : action angry
* date     : 2017/7/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_ANGRY__
#define __IE_ACTION_ANGRY__

#include "IEaction.h"

IE_BEGIN

class __IE_DLL__ IEActionAngry :public IEAction
{
public:
	IEActionAngry();
	virtual ~IEActionAngry();
	virtual void Initialization();
	static IEActionAngry * Create();

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();
};

IE_END

#endif