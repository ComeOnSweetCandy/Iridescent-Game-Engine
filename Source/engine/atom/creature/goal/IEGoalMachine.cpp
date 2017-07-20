#define __IE_DLL_EXPORTS__
#include "IEGoalMachine.h"
#include "../IECreature.h"

IE_BEGIN

IEGoalMachine::IEGoalMachine()
{
	m_creature = NULL;
}

IEGoalMachine::~IEGoalMachine()
{
	__IE_RELEASE_DIF__(m_goalList);
	__IE_RELEASE_DIF__(m_curGoal);
}

void IEGoalMachine::Initialization(IECreature * creature)
{
	m_goalList = IEStack::Create();
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

void IEGoalMachine::AddGoal(IEGoal * goal)
{
	if (m_curGoal == NULL)
	{
		m_curGoal = goal;
	}
	else
	{
		m_goalList->PushFromEnding(goal);
	}
}

void IEGoalMachine::ChangeGoal(IEGoal * goal)
{
	if (m_curGoal == NULL)
	{
		m_curGoal = goal;
	}
	else
	{
		__IE_RELEASE_DIF__(goal);
	}
}

void IEGoalMachine::Excute()
{
	if (m_curGoal)
	{
		m_curGoal->Excute();
	}
	else
	{
		if (IEGoal * nextGoal = (IEGoal *)(m_goalList->PopFromBegining()))
		{
			//���ȼ��goalջ �Ƿ���׼���õ���һ��Ŀ��
			m_curGoal = nextGoal;
			m_curGoal->Excute();
		}
		else
		{
			//���û��next goal ��Ҫ֪ͨcreature��
			m_creature->Await();
		}
	}
}

IE_END