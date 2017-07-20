#define __IE_DLL_EXPORTS__
#include "IEGoal.h"

#include "IEGoalMachine.h"

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

void IEGoal::FinishSelf()
{
	//m_goalMachine->FinishGoal(m_goalType);
}

void IEGoal::SetGoalMachine(IEGoalMachine * goalMachine)
{
	m_goalMachine = goalMachine;
}

IE_END