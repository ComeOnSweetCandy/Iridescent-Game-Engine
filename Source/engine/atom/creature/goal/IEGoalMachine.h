/***********************************
* name     : IEGoalMachine.h
* creater  : cosc
* info     : goal controller
* date     : 2017/6/22
* version  : 1.0
* remark   : 一个creature必须有一个goal管理器，同时最大允许一个goal在运行，goal可以有等待序列
************************************/

#ifndef __IE_GOAL_MACHINE__
#define __IE_GOAL_MACHINE__

#include "IEGoal.h"
#include "../../../../core/container/IEstack.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEGoalMachine:public IEObject
{
public:
	IEGoalMachine();
	virtual ~IEGoalMachine();
	virtual void Initialization(IECreature * creature);
	static IEGoalMachine * Create(IECreature * creature);

public:
	void Run();
	void AddGoal(IEGoal * goal);
	void ChangeGoal(IEGoal * goal);
	void FinishGoal(IEGoal * goal);

	void SetCreature(IECreature * creature);
	IECreature * GetCreature();

private:
	IEStack * m_goalList;
	IEGoal * m_curGoal;
	IECreature * m_creature;

	friend class IEGoal;
};

IE_END

#endif