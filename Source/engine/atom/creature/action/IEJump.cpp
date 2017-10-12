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

	//给予其一个向上的力
	IEPhysicNode * physicNode = GetCreature()->GetPhysicNode();
	if (physicNode->GetPhysicState() == __physic_state_static__)
	{
		physicNode->SetForward(0, 20.0f);
		physicNode->SetPhysicNodeState(__physic_state_air__);
	}
}

void IEJump::Excute()
{
	IEPhysicNode * physicNode = GetCreature()->GetPhysicNode();
	if (physicNode->GetPhysicState() == __physic_state_static__)
	{
		//当物理体再次变回static的时候
		GetActionMachine()->ChangeAction(NULL);
	}
}

void IEJump::End()
{
	GetCreature()->ChangeGroup("stop", __creature_part_leg__);
}

IE_END