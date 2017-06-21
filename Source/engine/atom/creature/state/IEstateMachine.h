/***********************************
* name     : IEstateMachine.h
* creater  : cosc
* info     : action control machine
* date     : 2017/1/14
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_STATE_MACHINE__
#define __IE_STATE_MACHINE__

#include "IEState.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEStateMachine:public IEObject
{
public:
	IEStateMachine();
	virtual ~IEStateMachine();
	virtual void Initialization(IECreature * creature);
	static IEStateMachine * Create(IECreature * creature);

protected:
	void ExcuteState();
	void CheckStates();

	bool AllowAddState(IEStateType stateType);
	void AddState(IEStateType stateType);
	void AddState(IEStateType stateType, IEState * state);
	void CreateState(IEStateType stateType);
	void DeleteState(IEStateType stateType);

private:
	IEState * m_stateList[__state_count__];
	IECreature * m_creature;

	friend class IEAction;
};

IE_END

#endif