/***********************************
* name     : IEactionMachine.h
* creater  : cosc
* info     : action control machine
* date     : 2017/1/14
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_MACHINE__
#define __IE_ACTION_MACHINE__

#include "IEaction.h"
#include "IEawait.h"
#include "IEattack.h"
#include "IEdisplacement.h"
#include "IEuseProp.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEActionMachine:public IEObject
{
public:
	IEActionMachine();
	virtual ~IEActionMachine();
	virtual void Initialization(IECreature * atom);
	static IEActionMachine * Create(IECreature * atom);

public:
	void ChangeAction(IEActionType actionType);
	void ChangeAction(IEActionType actionType, IEAction * action);
	void AppendAction(IEActionType actionType);
	void AppendAction(IEActionType actionType, IEAction * action);
	bool AllowChangeAction(IEAction * action);
	void DeleteAction(IEActionType actionType);
	void DeleteOtherActions(IEActionType actionType, IEActionLevel actionLevel);
	void DeleteAllActions();
	void CheckActions();
	void ExcuteAction();

private:
	void CreateAction(IEActionType actionType);

private:
	IEAction * m_actionList[__action_count__];
	IECreature * m_creature;
	IEString m_lastActionTextureName;

	friend class IEAction;
};

IE_END

#endif