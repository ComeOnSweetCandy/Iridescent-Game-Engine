/***********************************
* name     : IERest.h
* creater  : cosc
* info     : action rest
* date     : 2017/7/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_REST__
#define __IE_REST__

#include "IEaction.h"

IE_BEGIN

class __IE_DLL__ IERest:public IEAction
{
public:
	IERest();
	virtual ~IERest();
	virtual void Initialization();
	static IERest * Create();

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	float m_waitTime;
};

IE_END

#endif