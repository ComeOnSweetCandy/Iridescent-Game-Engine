/***********************************
* name     : IEGoalMachine.h
* creater  : cosc
* info     : goal controller
* date     : 2017/6/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_MACHINE__
#define __IE_GOAL_MACHINE__

#include "IEGoal.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEGoalMachine
{
public:
	IEGoalMachine();
	virtual ~IEGoalMachine();
	virtual void Initialization(IECreature * creature);
	static IEGoalMachine * Create(IECreature * creature);

public:
	void SetCreature(IECreature * creature);
	IECreature * GetCreature();

protected:
	void ExcuteGoal();
	bool CheckGoals();
	void SwitchGoal(IEGoalType goalType, IEGoal * goal = NULL);

private:
	IEGoal * m_goalList[__goal_count__];
	IECreature * m_creature;

	friend class IEState;
};

IE_END

#endif