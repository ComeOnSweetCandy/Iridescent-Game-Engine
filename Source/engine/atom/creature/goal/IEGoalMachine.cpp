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
	IEGoalMachine::SetCreature(creature);

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
	goal->SetGoalMachine(this);

	if (m_curGoal == NULL)
	{
		m_curGoal = goal;
		m_curGoal->Begin();
	}
	else
	{
		m_goalList->PushFromEnding(goal);
	}
}

void IEGoalMachine::ChangeGoal(IEGoal * goal)
{
	goal->SetGoalMachine(this);

	if (m_curGoal == NULL)
	{
		m_curGoal = goal;
		m_curGoal->Begin();
	}
	else
	{
		__IE_RELEASE_DIF__(goal);
	}
}

void IEGoalMachine::FinishGoal(IEGoal * goal)
{
	if (m_curGoal)
	{ 
		if (m_curGoal == goal)
		{
			__IE_RELEASE_DIF__(m_curGoal);
		}
	}
}

void IEGoalMachine::Run()
{
	if (m_curGoal)
	{
		m_curGoal->Excute();
	}
	else
	{
		if (IEGoal * nextGoal = (IEGoal *)(m_goalList->PopFromBegining()))
		{
			//首先检查goal栈 是否有准备好的下一个目标
			m_curGoal = nextGoal;
			m_curGoal->Begin();
		}
		else
		{
			//如果没有next goal 就要通知creature了
			m_creature->Await();
		}
	}
}

IE_END