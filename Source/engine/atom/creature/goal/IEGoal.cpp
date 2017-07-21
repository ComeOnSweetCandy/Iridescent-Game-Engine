#define __IE_DLL_EXPORTS__
#include "IEGoal.h"

#include "../IECreature.h"
#include "IEGoalMachine.h"
#include "../action/IEAction.h"

IE_BEGIN

IEGoal::IEGoal()
{
	m_goalType = __goal_count__;
}

IEGoal::~IEGoal()
{

}

void IEGoal::Initialization()
{

}

IEGoal * IEGoal::Create()
{
	return NULL;
}

IECreature * IEGoal::GetCreature()
{
	return m_goalMachine->m_creature;
}

void IEGoal::ChangeAction(IEAction * action)
{
	GetCreature()->GetActionMachine()->ChangeAction(action);
}

void IEGoal::FinishSelf()
{
	m_goalMachine->FinishGoal(this);
}

void IEGoal::SetGoalMachine(IEGoalMachine * machine)
{
	m_goalMachine = machine;
}

IE_END