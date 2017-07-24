/***********************************
* name     : IEGoal.h
* creater  : cosc
* info     : single goal
* date     : 2017/6/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL__
#define __IE_GOAL__

#include "../../../../core/IEobject.h"
#include "../../../../core/container/IEcontianer.h"
#include "../../../../type/IEvector.h"

IE_BEGIN

class IECreature;
class IEGoalMachine;
class IEAction;

class __IE_DLL__ IEGoal:public IEObject
{
public:
	IEGoal();
	virtual ~IEGoal();
	virtual void Initialization();
	static IEGoal * Create();

protected:
	virtual void Begin() = 0;
	virtual void Excute() = 0;
	virtual void End() = 0;

	IECreature * GetCreature();
	
	void ChangeAction(IEAction * action);
	void FinishSelf();

private:
	void SetGoalMachine(IEGoalMachine * machine);

protected:
	IEGoalMachine * m_goalMachine;

	unsigned int _Mask;				//作为一个自身的标志
	unsigned int _Opera;			//操作数 代表比哪些goal等级更高

	friend class IEGoalMachine;
};

IE_END

#endif