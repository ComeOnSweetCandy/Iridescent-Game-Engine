#define __IE_DLL_EXPORTS__
#include "IEdead.h"
#include "../atom/IEcreature.h"

IE_BEGIN

IEDead::IEDead()
{
	m_actionType = __action_dead__;
	m_actionLevel = __actionlevel_3__;
}

IEDead::~IEDead()
{

}

void IEDead::Initialization()
{

}

IEDead * IEDead::Create()
{
	IEDead * action = new IEDead();
	action->Initialization();
	return action;
}

bool IEDead::Begin()
{
	ChangeActionTexture("dead", 1);
	DeleteOtherActions();

	return true;
}

bool IEDead::Excute()
{
	return true;
}

bool IEDead::End()
{
	GetActionNode()->RemoveFromParent();

	return true;
}

IE_END