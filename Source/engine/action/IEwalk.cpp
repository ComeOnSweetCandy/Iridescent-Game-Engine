#define __IE_DLL_EXPORTS__
#include "IEwalk.h"

#include "../../interface/cmd/IEapplication.h"
#include "../scene/IEmap.h"

IE_BEGIN

IEWalk::IEWalk()
{
	m_actionType = __action_walk__;
	m_actionLevel = __actionlevel_0__;

	m_path = NULL;
	m_stepIndex = 0;
	m_destination = 0.0f;
}

IEWalk::~IEWalk()
{
	__IE_RELEASE__(m_path);
}

void IEWalk::Initialization(float x, float y)
{
	SetDestination(x, y);
}

IEWalk * IEWalk::Create(float x, float y)
{
	IEWalk * action = new IEWalk();
	action->Initialization(x, y);
	return action;
}

void IEWalk::SetDestination(float x, float y)
{
	m_destination = IEVector(x, y);
}

void IEWalk::FindPath()
{
	const float * translate = GetActionNode()->GetTranslate();
	IEVector startPosition(translate[0], translate[1]);
	m_path = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->FindPath(this->GetActionNode()->GetPhysicNode(), startPosition, m_destination);
	m_stepIndex = m_path->Count() - 1;

	m_destination = startPosition;
}

void IEWalk::GetNextStep()
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

bool IEWalk::Begin()
{
	FindPath();

	ChangeActionTexture("walk");
	DeleteOtherActions();
	return true;
}

bool IEWalk::Excute()
{
	if (m_stepIndex < -1)
	{
		DeleteAction(m_actionType);
		return false;
	}

	const float * translate = GetActionNode()->GetTranslate();

	IEVector leftRoad = m_destination - IEVector(translate[0], translate[1]);
	float speed = GetUnitInfo()->GetSpeed();
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
	IEAction::AppendAction(__action_displacement__, action);

	return true;
}

bool IEWalk::End()
{
	DeleteAnimation(m_animation);
	return true;
}

IE_END