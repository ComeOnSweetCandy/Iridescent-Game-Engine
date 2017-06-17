#define __IE_DLL_EXPORTS__
#include "IEsynchronizeAnimation.h"

IE_BEGIN

IESynchronizeAction::IESynchronizeAction()
{
	m_actionsList = IEContainer::Create();
	m_actionsList->Retain();
}

IESynchronizeAction::~IESynchronizeAction()
{
	m_actionsList->Release();
}

void IESynchronizeAction::Initialization()
{

}

IESynchronizeAction * IESynchronizeAction::Create()
{
	IESynchronizeAction * object = new IESynchronizeAction();
	object->Initialization();
	return object;
}

void IESynchronizeAction::CompletedAction(IENode * node)
{

}

void IESynchronizeAction::SetCircle()
{

}

void IESynchronizeAction::SetLoop()
{

}

bool IESynchronizeAction::Run(IENode * node)
{
	IEObject ** actions = m_actionsList->GetContainer();
	for (int index = 0; index < m_actionsList->Count(); index++)
	{
		IEAnimation * action = (IEAnimation *)actions[index];
		if (action->Run(node))
		{
			m_actionsList->Pop(action);
			index--;
		}
	}

	if (m_actionsList->Count() == 0)
	{
		return true;
	}
	return false;
}

void IESynchronizeAction::PushAction(IEAnimation * action)
{
	m_actionsList->Push(action);
}

void IESynchronizeAction::PushActions(IEAnimation ** actions, int actionsCount)
{
	m_actionsList->PushArrays((IEObject **)actions, actionsCount);
}

IE_END