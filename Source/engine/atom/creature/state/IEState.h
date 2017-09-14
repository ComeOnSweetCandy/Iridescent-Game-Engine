/***********************************
* name     : IEState.h
* creater  : cosc
* info     : single state
* date     : 2017/9/14
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_STATE__
#define __IE_STATE__

#include "../../../../core/IEobject.h"
#include "../../../../core/container/IEcontianer.h"
#include "../../../../type/IEvector.h"

IE_BEGIN

#define __IE_STATE_TYPE__				00000000000000000000000000000000
#define __IE_STATE_SLOW__				00000000000000000000000000000001
#define __IE_STATE_POISONED__			00000000000000000000000000000010

//记录state的类型
typedef unsigned int IEStateType;

class IECreature;
class IEStateMachine;
class IEAction;

class __IE_DLL__ IEState:public IEObject
{
public:
	IEState();
	virtual ~IEState();
	virtual void Initialization();
	static IEState * Create();

protected:
	virtual void Begin() = 0;
	virtual void Excute() = 0;
	virtual void End() = 0;

	IECreature * GetCreature();

	void FinishSelf();

private:
	void SetStateMachine(IEStateMachine * machine);

protected:
	IEStateMachine * m_stateMachine;

	IEStateType _Type;

	friend class IEStateMachine;
};

IE_END

#endif