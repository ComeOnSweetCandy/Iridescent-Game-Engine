#define __IE_DLL_EXPORTS__
#include "IEstateMachine.h"
#include "../atom/IEcreature.h"

IE_BEGIN

IEActionMachine::IEActionMachine()
{
	m_creature = NULL;
}

IEActionMachine::~IEActionMachine()
{
	m_creature = NULL;

	DeleteOtherActions(__action_count__, __actionlevel_99__);
}

void IEActionMachine::Initialization(IECreature * creature)
{
	m_creature = creature;
	for (int index = 0; index < __action_count__; index++)
	{
		m_actionList[index] = NULL;
	}
}

IEActionMachine * IEActionMachine::Create(IECreature * atom)
{
	IEActionMachine * object = new IEActionMachine();
	object->Initialization(atom);
	return object;
}

void IEActionMachine::ChangeAction(IEActionType actionType)
{
	if (m_actionList[actionType])
	{
		return;
	}

	CreateAction(actionType);
	m_actionList[actionType]->m_actionMachine = this;
	if (AllowChangeAction(m_actionList[actionType]))
	{
		m_actionList[actionType]->Begin();
	}
	else
	{
		m_actionList[actionType]->Release();
		m_actionList[actionType] = NULL;
	}
}

void IEActionMachine::ChangeAction(IEActionType actionType, IEAction * action)
{
	if (m_actionList[actionType])
	{
		action->Release();

		return;
	}

	m_actionList[actionType] = action;
	m_actionList[actionType]->m_actionMachine = this;
	if (AllowChangeAction(m_actionList[actionType]))
	{
		m_actionList[actionType]->Begin();
	}
	else
	{
		m_actionList[actionType]->Release();
		m_actionList[actionType] = NULL;
	}
}

void IEActionMachine::AppendAction(IEActionType actionType)
{
	if (m_actionList[actionType])
	{
		return;
	}

	CreateAction(actionType);
	m_actionList[actionType]->m_actionMachine = this;
	//m_actionList[actionType]->Begin();
}

void IEActionMachine::AppendAction(IEActionType actionType, IEAction * action)
{
	if (m_actionList[actionType])
	{
		return;
	}
	m_actionList[actionType] = action;
	m_actionList[actionType]->m_actionMachine = this;
	//m_actionList[actionType]->Begin();
}

bool IEActionMachine::AllowChangeAction(IEAction * action)
{
	IEActionLevel newActionLevel = action->m_actionLevel;

	for (int index = 0; index < __action_count__; index++)
	{
		if (m_actionList[index])
		{
			if (m_actionList[index]->m_actionLevel > newActionLevel)
			{
				return false;
			}
		}
	}

	return true;
}

void IEActionMachine::ExcuteAction()
{
	CheckActions();

	for (int index = 0; index < __action_count__; index++)
	{
		if (m_actionList[index])
		{
			m_actionList[index]->Excute();
		}
	}
}

void IEActionMachine::DeleteAction(IEActionType stateType)
{
	if (!m_actionList[stateType])
	{
		__IE_WARNING__("note : state does not exists\n");
		return;
	}
	
	m_actionList[stateType]->End();
	m_actionList[stateType]->Release();
	m_actionList[stateType] = NULL;
}

void IEActionMachine::CheckActions()
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_actionList[index])
		{
			return;
		}
	}
	ChangeAction(__action_await__);
}

void IEActionMachine::DeleteOtherActions(IEActionType actionType, IEActionLevel actionLevel)
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_actionList[index] && index != actionType && m_actionList[index]->m_actionLevel <= actionLevel)
		{
			m_actionList[index]->End();
			m_actionList[index]->Release();
			m_actionList[index] = NULL;
		}
	}
}

void IEActionMachine::DeleteAllActions()
{
	for (int index = 0; index < __action_count__; index++)
	{
		if (m_actionList[index])
		{
			m_actionList[index]->End();
			m_actionList[index]->Release();
			m_actionList[index] = NULL;
		}
	}
}

void IEActionMachine::CreateAction(IEActionType actionType)
{
	switch (actionType)
	{
	case IridescentEngine::__action_await__:
		m_actionList[actionType] = IEAwait::Create();
		break;
	case IridescentEngine::__action_attack__:
		m_actionList[actionType] = IEAttack::Create();
		break;
	case IridescentEngine::__action_useProp__:
		m_actionList[actionType] = IEUseProp::Create();
		break;
	case IridescentEngine::__action_displacement__:
		m_actionList[actionType] = IEDisplacement::Create();
		break;
	case IridescentEngine::__action_injured__:
		m_actionList[actionType] = NULL;
		break;
	default:
		break;
	}
}

IE_END