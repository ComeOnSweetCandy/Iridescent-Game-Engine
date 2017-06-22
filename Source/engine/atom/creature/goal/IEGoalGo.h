/***********************************
* name     : IEGoalGo.h
* creater  : cosc
* info     : single goal go
* date     : 2017/6/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_GOAL_GO__
#define __IE_GOAL_GO__

#include "IEGoal.h"

IE_BEGIN

class __IE_DLL__ IEGoalGo:public IEGoal
{
public:
	IEGoalGo();
	virtual ~IEGoalGo();
	virtual void Initialization(float x, float y);
	static IEGoalGo * Create(float x, float y);

public:
	void SetDestination(float x, float y);

protected:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

private:
	void FindPath();

private:
	IEVector m_destination;
	IEArray * m_path;
	int m_stepIndex;
};

IE_END

#endif