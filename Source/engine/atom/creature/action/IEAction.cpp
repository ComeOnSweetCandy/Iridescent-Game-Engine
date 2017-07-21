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

void IEAction::ChangeTextureGroup(const char * groupName)
{
	GetCreature()->ChangeGroup(groupName);
}

void IEAction::SetActionMachine(IEActionMachine * machine)
{
	m_actionMachine = machine;
}

IE_END