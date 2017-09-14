#define __IE_DLL_EXPORTS__
#include "IEState.h"

#include "../IECreature.h"
#include "IEStateMachine.h"

IE_BEGIN

IEState::IEState()
{

}

IEState::~IEState()
{

}

void IEState::Initialization()
{

}

IEState * IEState::Create()
{
	return NULL;
}

IECreature * IEState::GetCreature()
{
	return m_stateMachine->m_creature;
}

void IEState::FinishSelf()
{
	m_stateMachine->FinishState(this);
}

void IEState::SetStateMachine(IEStateMachine * machine)
{
	m_stateMachine = machine;
}

IE_END