/***********************************
* name     : IEGoal.h
* creater  : cosc
* info     : single goal
* date     : 2017/6/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL__
#define __IE_GOAL__

#include "../../../../core/IEobject.h"
#include "../../../../core/container/IEcontianer.h"
#include "../../../../type/IEvector.h"

IE_BEGIN

class IEGoalMachine;

enum __IE_DLL__ IEGoalType
{
	__goal_await__,
	__goal_go__,
	__goal_flee__,
	__goal_follow__,
	__goal_attack__,
	__goal_count__
};

class __IE_DLL__ IEGoal:public IEObject
{
public:
	IEGoal();
	virtual ~IEGoal();
	virtual void Initialization();
	static IEGoal * Create();

protected:
	virtual void Begin() = 0;
	virtual void Excute() = 0;
	virtual void End() = 0;

	void FinishSelf();

private:
	void SetGoalMachine(IEGoalMachine * stateMachine);

protected:
	IEGoalType m_goalType;
	IEGoalMachine * m_goalMachine;

	friend class IEGoalMachine;
};

IE_END

#endif