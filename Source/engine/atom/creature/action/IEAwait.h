/***********************************
* name     : IEawait.h
* creater  : cosc
* info     : state await
* c_date   : 2017/1/13
* l_date   : 2017/1/13
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_AWAIT__
#define __IE_AWAIT__

#include "IEaction.h"

IE_BEGIN

class __IE_DLL__ IEAwait:public IEAction
{
public:
	IEAwait();
	virtual ~IEAwait();
	virtual void Initialization();
	static IEAwait * Create();

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

private:
	float m_waitTime;
};

IE_END

#endif