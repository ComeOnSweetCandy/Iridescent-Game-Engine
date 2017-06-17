/***********************************
* name     : IEwander.h
* creater  : cosc
* info     : wander to somewhere
* date     : 2016/12/9
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_EXECUTE__
#define __IE_EXECUTE__

#include "../IEnode.h"
#include "IEanimation.h"

IE_BEGIN

class IEExecute :public IEAnimation
{
public:
	IEExecute();
	virtual ~IEExecute();
	virtual void Initialization();
	static IEExecute * Create();

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

private:

};

IE_END

#endif