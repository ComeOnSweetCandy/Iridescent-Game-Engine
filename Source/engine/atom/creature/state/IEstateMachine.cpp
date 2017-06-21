#define __IE_DLL_EXPORTS__
#include "IEstateMachine.h"
#include "../../IEcreature.h"

IE_BEGIN

IEStateMachine::IEStateMachine()
{
	m_creature = NULL;
}

IEStateMachine::~IEStateMachine()
{
	m_creature = NULL;
}

void IEStateMachine::Initialization(IECreature * creature)
{
	m_creature = creature;
	for (int index = 0; index < __action_count__; index++)
	{
		m_stateList[index] = NULL;
	}
}

IEStateMachine * IEStateMachine::Create(IECreature * creature)
{
	IEStateMachine * object = new IEStateMachine();
	object->Initialization(creature);
	return object;
}

bool IEStateMachine::AllowAddState(IEStateType stateType)
{

}

void IEStateMachine::AddState(IEStateType stateType)
{
	if (m_stateList[stateType])
	{
		return;
	}

	CreateState(stateType);
	m_stateList[stateType]->m_stateMachine = this;

	if (AllowAddState(m_stateList[stateType]))
	{
		m_stateList[stateType]->Begin();
	}
	else
	{
		delete m_stateList[stateType];
		m_stateList[stateType] = NULL;
	}
}

void IEStateMachine::AddState(IEStateType stateType, IEState * state)
{
	if (m_stateList[stateType])
	{
		delete state;

		return;
	}

	m_stateList[stateType] = state;
	m_stateList[stateType]->m_stateMachine = this;

	if (AllowAddState(m_stateList[stateType]))
	{
		m_stateList[stateType]->Begin();
	}
	else
	{
		delete m_stateList[stateType];
		m_stateList[stateType] = NULL;
	}
}

void IEStateMachine::ExcuteState()
{
	CheckStates();

	for (int index = 0; index < __action_count__; index++)
	{
		if (m_stateList[index])
		{
			m_stateList[index]->Excute();
		}
	}
}

void IEStateMachine::DeleteState(IEStateType stateType)
{
	if (m_stateList[stateType])
	{
		delete m_stateList[stateType];
		m_stateList[stateType] = NULL;
	}
}

void IEStateMachine::CheckStates()
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_stateList[index])
		{
			return;
		}
	}
	AddState(__state_free__);
}

void IEStateMachine::CreateState(IEStateType stateType)
{
	m_stateList[stateType] = IEState::Create();
}

IE_END