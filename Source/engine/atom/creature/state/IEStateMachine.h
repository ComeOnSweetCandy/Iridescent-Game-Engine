/***********************************
* name     : IEStateMachine.h
* creater  : cosc
* info     : state controller
* date     : 2017/9/14
* version  : 1.0
* remark   : 一个creature必须有一个state管理器 允许同时运行多个state
************************************/

#ifndef __IE_STATE_MACHINE__
#define __IE_STATE_MACHINE__

#include "IEState.h"

#include "../../../../core/container/IEstack.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEStateMachine :public IEObject
{
public:
	IEStateMachine();
	virtual ~IEStateMachine();
	virtual void Initialization(IECreature * creature);
	static IEStateMachine * Create(IECreature * creature);

public:
	void Run();
	void AddGoal(IEState * goal);
	void FinishState(IEState * goal);

	void SetCreature(IECreature * creature);
	IECreature * GetCreature();

private:
	IEStack * m_stateList;
	IECreature * m_creature;

	friend class IEState;
};

IE_END

#endif