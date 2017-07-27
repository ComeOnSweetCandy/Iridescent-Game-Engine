#define __IE_DLL_EXPORTS__
#include "IEGoalGo.h"

#include "IEGoalMachine.h"
#include "../../../../interface/cmd/IEapplication.h"
#include "../../../scene/IEmap.h"

#include "../action/IEActionDisplacement.h"

IE_BEGIN

IEGoalGo::IEGoalGo()
{
	m_path = NULL;
	m_stepIndex = 0;
}

IEGoalGo::~IEGoalGo()
{

}

void IEGoalGo::Initialization(float x, float y)
{
	IEGoalGo::SetDestination(x, y);
}

IEGoalGo * IEGoalGo::Create(float x, float y)
{
	IEGoalGo * goal = new IEGoalGo();
	goal->Initialization(x, y);
	return goal;
}

void IEGoalGo::SetDestination(float x, float y)
{
	m_destination[0] = x;
	m_destination[1] = y;
}

void IEGoalGo::Begin()
{
	FindPath();
	
	//ChangeActionTexture("walk");
	//DeleteOtherActions();
	//return true;
}

void IEGoalGo::Excute()
{
	if (m_stepIndex < -1)
	{
		IEGoal::FinishSelf();

		return;
	}

	IECreature * creature = m_goalMachine->GetCreature();
	IEActionMachine * actionMachine = creature->GetActionMachine();
	const float * translate = creature->GetTranslate();

	IEVector leftRoad = m_destination - IEVector(translate[0], translate[1]);
	float speed = creature->GetCreatureUnit()->_Speed;
	if (leftRoad.Length() < (speed / 60.0f))
	{
		GetNextStep();
	}
	else
	{
		leftRoad.Normalize();
		leftRoad = leftRoad * speed * IETime::Share()->GetLastFrapPassingTime();
	}

	IEDisplacement * action = IEDisplacement::Create(leftRoad.m_x, leftRoad.m_y);
	actionMachine->ChangeAction(action);
}

void IEGoalGo::End()
{

}

void IEGoalGo::GetNextStep()
{
	if (m_stepIndex >= 0)
	{
		IEObject ** objects = m_path->GetContainer();
		m_destination = *((IEVector *)objects[m_stepIndex]);
		m_stepIndex--;
	}
	else
	{
		m_stepIndex--;
	}
}

void IEGoalGo::FindPath()
{
	IECreature * creature = m_goalMachine->GetCreature();
	const float * translate = creature->GetTranslate();
	IEVector startPosition(translate[0], translate[1]);
	m_path = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->FindPath(creature->GetPhysicNode(), startPosition, m_destination);
	m_stepIndex = m_path->Count() - 1;
	m_destination = startPosition;
}

IE_END