#define __IE_DLL_EXPORTS__
#include "IEGoalMachine.h"
#include "../../IEcreature.h"

IE_BEGIN

IEGoalMachine::IEGoalMachine()
{
	m_creature = NULL;
}

IEGoalMachine::~IEGoalMachine()
{
	m_creature = NULL;
}

void IEGoalMachine::Initialization(IECreature * creature)
{
	m_creature = creature;
	for (int index = 0; index < __action_count__; index++)
	{
		m_goalList[index] = NULL;
	}
}

IEGoalMachine * IEGoalMachine::Create(IECreature * creature)
{
	IEGoalMachine * object = new IEGoalMachine();
	object->Initialization(creature);
	return object;
}

void IEGoalMachine::SetCreature(IECreature * creature)
{
	m_creature = creature;
}

IECreature * IEGoalMachine::GetCreature()
{
	return m_creature;
}

void IEGoalMachine::ExcuteGoal()
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_goalList[index])
		{
			m_goalList[index]->Excute();
		}
	}
}

void IEGoalMachine::SwitchGoal(IEGoalType goalType, IEGoal * goal)
{
	if (m_goalList[goalType])
	{
		delete m_goalList[goalType];
		m_goalList[goalType] = NULL;
	}

	if (!goal)
	{
		switch (goalType)
		{
		case IridescentEngine::__goal_go__:
			break;
		case IridescentEngine::__goal_flee__:
			break;
		case IridescentEngine::__goal_follow__:
			break;
		case IridescentEngine::__goal_attack__:
			break;
		case IridescentEngine::__goal_count__:
			break;
		default:
			break;
		}

		m_goalList[goalType] = NULL;
	}

	m_goalList[goalType] = goal;
	m_goalList[goalType]->SetGoalMachine(this);
}

bool IEGoalMachine::CheckGoals()
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_goalList[index])
		{
			return false;
		}
	}

	return true;
}

IE_END