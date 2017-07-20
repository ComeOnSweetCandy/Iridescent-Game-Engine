/***********************************
* name     : IEGoalUser.h
* creater  : cosc
* info     : user controll goal
* date     : 2017/7/20
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_USER__
#define __IE_GOAL_USER__

#include "IEGoal.h"

IE_BEGIN

class __IE_DLL__ IEGoalUser :public IEGoal
{
public:
	IEGoalUser();
	virtual ~IEGoalUser();
	virtual void Initialization();
	static IEGoalUser * Create();

protected:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
};

IE_END

#endif