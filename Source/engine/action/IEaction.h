/***********************************
* name     : IEstate.h
* creater  : cosc
* info     : state base
* date     : 2017/1/13
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION__
#define __IE_ACTION__

#include "../atom/creature/IEcreatureInfo.h"
#include "../../core/IEnode.h"
#include "../trigger/IEtrigger.h"

IE_BEGIN

class IEActionMachine;
class IECreature;

enum __IE_DLL__ IEActionType
{
	__action_await__ = 0, 
	__action_vertigo__,			//state or actioned
	__action_walk__,			//action
	__action_displacement__,	//action
	__action_blink__,			//action
	__action_attack__,			//action
	__action_cast__,			//action
	__action_useProp__,			//action
	__action_injured__,			//state or actioned
	__action_dead__,			//state
	__action_count__			//
};

enum __IE_DLL__ IEActionLevel
{
	__actionlevel_0__,
	__actionlevel_1__,
	__actionlevel_2__,
	__actionlevel_3__,
	__actionlevel_99__
};

class __IE_DLL__ IEAction
{
public:
	IEAction();
	virtual ~IEAction();
	virtual void Initialization();
	virtual void Release();
	static IEAction * Create();

protected:
	virtual bool Begin() = 0;
	virtual bool Excute() = 0;
	virtual bool End() = 0;

	IENode * GetActionNode();
	IECreature * GetActionCreature();
	IECreatureInfo * GetCreatureInfo();
	IEUnitInfo * GetUnitInfo();

	void ChangeAction(IEActionType actionType);
	void ChangeAction(IEActionType actionType, IEAction * action);
	void AppendAction(IEActionType actionType);
	void AppendAction(IEActionType actionType, IEAction * action);
	void DeleteAction(IEActionType actionType);
	void DeleteOtherActions();
	void ChangeActionTexture(char * stateSuffix, int playTimes = 0);

	void AddAnimation(IEAnimation * animation);
	void DeleteAnimation(IEAnimation * animation);
	void ClearAndAddAnimation(IEAnimation * animation);

protected:
	IEActionType m_actionType;
	IEActionMachine * m_actionMachine;
	IEAnimation * m_animation;
	IEActionLevel m_actionLevel;

	friend class IEActionMachine;
};

IE_END

#endif