#define __IE_DLL_EXPORTS__
#include "IEJump.h"

#include "../IECreature.h"

IE_BEGIN

IEJump::IEJump()
{
	m_jumping = true;
}

IEJump::~IEJump()
{

}

void IEJump::Initialization()
{

}

IEJump * IEJump::Create()
{
	IEJump * action = new IEJump();
	action->Initialization();
	return action;
}

void IEJump::Begin()
{
	GetCreature()->ChangeGroup("jump", __creature_part_leg__);
}

void IEJump::Excute()
{

}

void IEJump::End()
{
	GetCreature()->ChangeGroup("stop", __creature_part_leg__);
}

IE_END