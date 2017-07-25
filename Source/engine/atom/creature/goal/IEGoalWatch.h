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

typedef enum __ieGoalWatchState
{
	__goal_watch_rest_state__,
	__goal_watch_angry_state__
}IEGoalWatchState;

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
	bool m_watchSomething;				//是否有监视到creature 放置重复转换状态
	IEGoalWatchState m_watchState;		//当前creature watch状况下的状态
	unsigned char m_cycle;				//检测周期 并非每一帧都会进行检测 而是几帧进行一次
};

IE_END

#endif