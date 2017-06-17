/***********************************
* name     : IEsynchronizeAction.h
* creater  : cosc
* info     : serveal actions playing at the moment time
* date     : 2016/12/7
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_SYNCHRONIZE__
#define __IE_ACTION_SYNCHRONIZE__

#include "../IEnode.h"
#include "IEanimation.h"
#include "../container/IEcontianer.h"

IE_BEGIN

class IESynchronizeAction:public IEAnimation
{
public:
	IESynchronizeAction();
	~IESynchronizeAction();
	virtual void Initialization();
	static IESynchronizeAction * Create();

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

	void PushAction(IEAnimation * action);
	void PushActions(IEAnimation ** actions, int actionsCount);

private:
	IEContainer * m_actionsList;
};

IE_END

#endif