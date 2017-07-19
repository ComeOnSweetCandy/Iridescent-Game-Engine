/***********************************
* name     : IEGoalMachine.h
* creater  : cosc
* info     : goal controller
* date     : 2017/6/22
* version  : 1.0
* remark   : һ��creature������һ��goal��������ͬʱ�������һ��goal�����У�goal�����еȴ�����
************************************/

#ifndef __IE_GOAL_MACHINE__
#define __IE_GOAL_MACHINE__

#include "IEGoal.h"
#include "../../../../core/container/IEstack.h"

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
	void FinishGoal(IEGoalType goalType);

	IECreature * GetCreatureByIndex(unsigned int index);

private:
	IEGoal * m_goalList[__goal_count__];
	IEGoal * m_curGoal;
	IECreature * m_creature;

	friend class IEGoal;
};

IE_END

#endif