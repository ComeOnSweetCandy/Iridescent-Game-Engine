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

IE_BEGIN

class IECreature;

class __IE_DLL__ IEStateMachine:public IEObject
{
public:
	IEStateMachine();
	virtual ~IEStateMachine();
	virtual void Initialization(IECreature * atom);
	static IEStateMachine * Create(IECreature * atom);

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