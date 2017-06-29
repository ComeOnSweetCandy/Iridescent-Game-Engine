/***********************************
* name     : IEGoalTarget.h
* creater  : cosc
* info     : single goal target
* date     : 2017/6/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_TARGET__
#define __IE_GOAL_TARGET__

#include "IEGoal.h"

IE_BEGIN

class __IE_DLL__ IEGoalTarget :public IEGoal
{
public:
	IEGoalTarget();
	virtual ~IEGoalTarget();
	virtual void Initialization(unsigned int targetIndex);
	static IEGoalTarget * Create(unsigned int targetIndex);

public:
	void SetTarget(unsigned int targetIndex);

protected:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	IEVector m_destination;
	IEArray * m_path;
	int m_stepIndex;
};

IE_END

#endif