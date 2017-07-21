/***********************************
* name     : IEActionMachine.h
* creater  : cosc
* info     : action control machine
* date     : 2017/1/14
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_MACHINE__
#define __IE_ACTION_MACHINE__

#include "IEAction.h"

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
	void ChangeAction(IEAction * action);
	void Run();

private:
	IEAction * m_action;
	IECreature * m_creature;

	friend class IEAction;
};

IE_END

#endif