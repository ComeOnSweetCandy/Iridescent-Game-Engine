#define __IE_DLL_EXPORTS__
#include "IEactionMachine.h"
#include "../IECreature.h"

IE_BEGIN

IEActionMachine::IEActionMachine()
{
	m_creature = NULL;
}

IEActionMachine::~IEActionMachine()
{
	m_creature = NULL;
}

void IEActionMachine::Initialization(IECreature * creature)
{
	m_creature = creature;
}

IEActionMachine * IEActionMachine::Create(IECreature * atom)
{
	IEActionMachine * object = new IEActionMachine();
	object->Initialization(atom);
	return object;
}

void IEActionMachine::ChangeAction(IEAction * action)
{
	action->SetActionMachine(this);

	if (m_action)
	{
		__IE_RELEASE_DIF__(action);
	}
	m_action = action;
	m_action->Begin();
}

void IEActionMachine::Run()
{
	if (m_action)
	{
		m_action->Excute();
	}
}

IE_END