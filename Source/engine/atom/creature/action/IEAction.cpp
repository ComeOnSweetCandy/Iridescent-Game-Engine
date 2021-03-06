#define __IE_DLL_EXPORTS__
#include "IEAction.h"

#include "IEActionMachine.h"
#include "../IECreature.h"

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

IEAction * IEAction::Create()
{
	return NULL;
}

IECreature * IEAction::GetCreature()
{
	return m_actionMachine->m_creature;
}

IEActionMachine * IEAction::GetActionMachine()
{
	return m_actionMachine;
}

void IEAction::KeyframeCallback()
{
	printf("key frame call back\n");
}

void IEAction::SetActionMachine(IEActionMachine * machine)
{
	m_actionMachine = machine;
}

IE_END