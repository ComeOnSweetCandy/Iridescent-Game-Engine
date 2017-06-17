/***********************************
* name     : IEdead.h
* creater  : cosc
* info     : action injured
* c_date   : 2017/3/29
* l_date   : 2017/3/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DEAD__
#define __IE_DEAD__

#include "IEaction.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEDead :public IEAction
{
public:
	IEDead();
	virtual ~IEDead();
	virtual void Initialization();
	static IEDead * Create();

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();
};

IE_END

#endif