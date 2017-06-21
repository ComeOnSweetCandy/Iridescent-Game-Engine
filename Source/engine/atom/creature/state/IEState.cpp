#define __IE_DLL_EXPORTS__
#include "IEState.h"

#include "IEstateMachine.h"

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

void IEState::DeleteAction(IEActionType actionType)
{
	m_actionMachine->DeleteAction(actionType);
}

void IEState::ChangeAction(IEActionType actionType)
{
	m_actionMachine->ChangeAction(actionType);
}

void IEState::ChangeAction(IEActionType actionType, IEState * action)
{
	m_actionMachine->ChangeAction(actionType, action);
}

void IEState::AppendAction(IEActionType actionType)
{
	m_actionMachine->AppendAction(actionType);
}

void IEState::AppendAction(IEActionType actionType, IEState * action)
{
	m_actionMachine->AppendAction(actionType, action);
}

void IEState::DeleteOtherActions()
{
	m_actionMachine->DeleteOtherActions(m_actionType, m_actionLevel);
}

IENode * IEState::GetActionNode()
{
	return (IENode *)(m_actionMachine->m_creature);
}

IECreature * IEState::GetActionCreature()
{
	return m_actionMachine->m_creature;
}

IECreatureInfo * IEState::GetCreatureInfo()
{
	return m_actionMachine->m_creature->GetCreatureInfo();
}

IEUnitInfo * IEState::GetUnitInfo()
{
	return m_actionMachine->m_creature->GetUnitInfo();
}

IE_END