/***********************************
* name     : IEinjured.h
* creater  : cosc
* info     : action injured
* c_date   : 2017/3/10
* l_date   : 2017/3/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INJURED__
#define __IE_INJURED__

#include "IEaction.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEInjured :public IEAction
{
public:
	IEInjured();
	virtual ~IEInjured();
	virtual void Initialization();
	static IEInjured * Create();

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();
};

IE_END

#endif