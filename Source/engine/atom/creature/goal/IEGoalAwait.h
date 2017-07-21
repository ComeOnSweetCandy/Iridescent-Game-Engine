/***********************************
* name     : IEGoalAwait.h
* creater  : cosc
* info     : single goal await
* date     : 2017/7/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_AWAIT__
#define __IE_GOAL_AWAIT__

#include "IEGoal.h"

IE_BEGIN

class __IE_DLL__ IEGoalAwait :public IEGoal
{
public:
	IEGoalAwait();
	virtual ~IEGoalAwait();
	virtual void Initialization();
	static IEGoalAwait * Create();

protected:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	
};

IE_END

#endif