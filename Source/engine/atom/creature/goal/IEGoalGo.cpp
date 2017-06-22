#define __IE_DLL_EXPORTS__
#include "IEGoalGo.h"

#include "IEGoalMachine.h"
#include "../../../../interface/cmd/IEapplication.h"
#include "../../../scene/IEmap.h"

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
	SetDestination(x, y);
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

bool IEGoalGo::Begin()
{

}

bool IEGoalGo::Excute()
{

}

bool IEGoalGo::End()
{

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