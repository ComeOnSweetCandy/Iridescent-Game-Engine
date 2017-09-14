#define __IE_DLL_EXPORTS__
#include "IEStateMachine.h"

#include "../IECreature.h"

IE_BEGIN

IEStateMachine::IEStateMachine()
{
	m_creature = NULL;
}

IEStateMachine::~IEStateMachine()
{
	__IE_RELEASE_DIF__(m_stateList);
}

void IEStateMachine::Initialization(IECreature * creature)
{
	IEStateMachine::SetCreature(creature);

	m_stateList = IEStack::Create();
}

IEStateMachine * IEStateMachine::Create(IECreature * creature)
{
	IEStateMachine * object = new IEStateMachine();
	object->Initialization(creature);
	return object;
}

void IEStateMachine::SetCreature(IECreature * creature)
{
	m_creature = creature;
}

IECreature * IEStateMachine::GetCreature()
{
	return m_creature;
}

void IEStateMachine::AddGoal(IEState * goal)
{
	goal->SetStateMachine(this);
}

void IEStateMachine::FinishState(IEState * goal)
{
	//if (m_curGoal)
	//{ 
	//	if (m_curGoal == goal)
	//	{
	//		__IE_RELEASE_DIF__(m_curGoal);
	//	}
	//}
}

void IEStateMachine::Run()
{
	//if (m_curGoal)
	//{
	//	m_curGoal->Excute();
	//}
	//else
	//{
	//	if (IEGoal * nextGoal = (IEGoal *)(m_stateList->PopFromBegining()))
	//	{
	//		//首先检查goal栈 是否有准备好的下一个目标
	//		m_curGoal = nextGoal;
	//		m_curGoal->Begin();
	//	}
	//	else
	//	{
	//		//如果没有next goal 就要通知creature了
	//		m_creature->Await();
	//	}
	//}
}

IE_END