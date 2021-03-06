#define __IE_DLL_EXPORTS__
#include "IEGoalTarget.h"

#include "IEGoalMachine.h"
#include "../../../../interface/cmd/IEapplication.h"
#include "../../../scene/IEmap.h"

//#include "../action/IEActionWalk.h"

IE_BEGIN

IEGoalTarget::IEGoalTarget()
{
	m_path = NULL;
	m_stepIndex = 0;
}

IEGoalTarget::~IEGoalTarget()
{

}

void IEGoalTarget::Initialization(unsigned int targetIndex)
{
	//SetDestination(x, y);
}

IEGoalTarget * IEGoalTarget::Create(unsigned int targetIndex)
{
	IEGoalTarget * goal = new IEGoalTarget();
	goal->Initialization(targetIndex);
	return goal;
}

//void IEGoalTarget::SetDestination(float x, float y)
//{
//	m_destination[0] = x;
//	m_destination[1] = y;
//}
//
//void IEGoalTarget::GetNextStep()
//{
//	if (m_stepIndex >= 0)
//	{
//		IEObject ** objects = m_path->GetContainer();
//		m_destination = *((IEVector *)objects[m_stepIndex]);
//		m_stepIndex--;
//	}
//	else
//	{
//		m_stepIndex--;
//	}
//}

//void IEGoalTarget::FindPath()
//{
//	IECreature * creature = m_goalMachine->GetCreature();
//	const float * translate = creature->GetTranslate();
//	IEVector startPosition(translate[0], translate[1]);
//	m_path = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->FindPath(creature->GetPhysicNode(), startPosition, m_destination);
//	m_stepIndex = m_path->Count() - 1;
//	m_destination = startPosition;
//}

void IEGoalTarget::Begin()
{
	//FindPath();

	//ChangeActionTexture("walk");
	//DeleteOtherActions();
	//return true;
}

void IEGoalTarget::Excute()
{
	//必须检测一次 目标是否存在
	//第二检测目标的位置是否有过引动 所以需要一个单位存储目标的位置

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
		//GetNextStep();
	}
	else
	{
		leftRoad.Normalize();
		leftRoad = leftRoad * speed * IETime::Share()->GetLastFrapPassingTime();
	}

	//IEActionWalk * action = IEActionWalk::Create(leftRoad.m_x, leftRoad.m_y);
	//actionMachine->ChangeAction(__action_displacement__, action);
}

void IEGoalTarget::End()
{
	//DeleteAnimation(m_animation);
}

IE_END