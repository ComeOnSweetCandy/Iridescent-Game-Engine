/***********************************
* name     : IEGoalAwait.h
* creater  : cosc
* info     : single goal watch
* date     : 2017/7/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_WATCH__
#define __IE_GOAL_WATCH__

#include "IEGoal.h"

IE_BEGIN

class __IE_DLL__ IEGoalWatch :public IEGoal
{
public:
	IEGoalWatch();
	virtual ~IEGoalWatch();
	virtual void Initialization();
	static IEGoalWatch * Create();

protected:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	unsigned char m_cycle;		//检测周期 并非每一帧都会进行检测 而是几帧进行一次
};

IE_END

#endif