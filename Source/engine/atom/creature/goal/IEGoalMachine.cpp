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

			return;
		}
	}

	//如果没有goal
	//creature'state swtich to free.
}

void IEGoalMachine::SwitchGoal(IEGoalType goalType, IEGoal * goal)
{
	if (!goal)
	{
		__IE_ERROR__("IEGaolMachine : error.\n");
	}

	//清空其它目标
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_goalList[index])
		{
			m_goalList[index]->End();
			delete m_goalList[index];
			m_goalList[index] = NULL;
		}
	}

	m_goalList[goalType] = goal;
	m_goalList[goalType]->SetGoalMachine(this);
	m_goalList[goalType]->Begin();
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

void IEGoalMachine::FinishGoal(IEGoalType goalType)
{
	if (m_goalList[goalType])
	{
		m_goalList[goalType]->End();
		delete m_goalList[goalType];
		m_goalList[goalType] = NULL;
	}
}

IE_END