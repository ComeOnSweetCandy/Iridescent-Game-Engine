/***********************************
* name     : IEstate.h
* creater  : cosc
* info     : state base every single state with a script function.
* date     : 2017/6/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_STATE__
#define __IE_STATE__

#include "../IEcreatureInfo.h"
#include "../../../../core/IEnode.h"
#include "../../../action/IEactionMachine.h"

IE_BEGIN

class IEStateMachine;
class IECreature;

enum __IE_DLL__ IEStateType
{
	__state_free__,				//state free
	__state_count__
};

class __IE_DLL__ IEState
{
public:
	IEState();
	virtual ~IEState();
	virtual void Initialization();
	static IEState * Create();

protected:
	virtual bool Begin() = 0;
	virtual bool Excute() = 0;
	virtual bool End() = 0;

	IECreature * GetCreature();
	IECreatureInfo * GetCreatureInfo();
	IEUnitInfo * GetUnitInfo();

	void ChangeAction(IEActionType actionType);
	void ChangeAction(IEActionType actionType, IEAction * action);
	void DeleteAction(IEActionType actionType);
	void DeleteAllActions();

protected:
	IEStateType m_stateType;
	IEStateMachine * m_stateMachine;

	friend class IEStateMachine;
};

IE_END

#endif