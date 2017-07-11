#define __IE_DLL_EXPORTS__
#include "IEAction.h"
#include "IEActionMachine.h"
#include "../atom/IEcreature.h"

IE_BEGIN

IEAction::IEAction()
{

}

IEAction::~IEAction()
{
	
}

void IEAction::Initialization()
{

}

void IEAction::Release()
{
	delete this;
}

IEAction * IEAction::Create()
{
	return NULL;
}

void IEAction::DeleteAction(IEActionType actionType)
{
	m_actionMachine->DeleteAction(actionType);
}

void IEAction::ChangeAction(IEActionType actionType)
{
	m_actionMachine->ChangeAction(actionType);
}

void IEAction::ChangeAction(IEActionType actionType, IEAction * action)
{
	m_actionMachine->ChangeAction(actionType, action);
}

void IEAction::AppendAction(IEActionType actionType)
{
	m_actionMachine->AppendAction(actionType);
}

void IEAction::AppendAction(IEActionType actionType, IEAction * action)
{
	m_actionMachine->AppendAction(actionType, action);
}

void IEAction::DeleteOtherActions()
{
	m_actionMachine->DeleteOtherActions(m_actionType, m_actionLevel);
}

IENode * IEAction::GetActionNode()
{
	return (IENode *)(m_actionMachine->m_creature);
}

IECreature * IEAction::GetActionCreature()
{
	return m_actionMachine->m_creature;
}

IECreatureInfo * IEAction::GetCreatureInfo()
{
	return m_actionMachine->m_creature->GetCreatureInfo();
}

IEUnitInfo * IEAction::GetUnitInfo()
{
	return m_actionMachine->m_creature->GetUnitInfo();
}

void IEAction::ChangeActionTexture(char * actionSuffix, int playTimes)
{
	if (m_actionMachine->m_lastActionTextureName == actionSuffix)
	{
		return;
	}

	m_actionMachine->m_lastActionTextureName = actionSuffix;
	IECreature * creature = m_actionMachine->m_creature;
	IEString textureGroupName = creature->GetTextureGroupName();
	IEString body = textureGroupName + "/" + actionSuffix;

	if (playTimes == 0)
	{
		//creature->ChangeTexture((body + ".png").GetString());
		creature->ChangeGroup(actionSuffix);
	}
	else
	{
		//creature->ChangeTextureOnce((body + ".png").GetString());
		creature->ChangeGroup(actionSuffix, 1);
	}
}

void IEAction::AddAnimation(IEAnimation * animation)
{
	IECreature * creature = m_actionMachine->m_creature;
	creature->AddAnimation(animation);
}

void IEAction::DeleteAnimation(IEAnimation * animation)
{
	if (animation)
	{
		IECreature * creature = m_actionMachine->m_creature;
		creature->DeleteAnimation(animation);
	}
}

void IEAction::ClearAndAddAnimation(IEAnimation * animation)
{
	IECreature * creature = m_actionMachine->m_creature;
	creature->ClearAnimations();
	creature->AddAnimation(animation);
}

IE_END