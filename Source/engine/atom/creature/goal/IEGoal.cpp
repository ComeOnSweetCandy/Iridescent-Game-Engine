#define __IE_DLL_EXPORTS__
#include "IEGoal.h"

#include "IEGoalMachine.h"

IE_BEGIN

IEGoal::IEGoal()
{

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

void IEGoal::SetGoalMachine(IEGoalMachine * goalMachine)
{
	m_goalMachine = goalMachine;
}

IE_END