#define __IE_DLL_EXPORTS__
#include "IEinteractionTrigger.h"

IE_BEGIN

IEInteractionTrigger::IEInteractionTrigger()
{
	m_triggerType = __trigger_interaction_type__;
}

IEInteractionTrigger::~IEInteractionTrigger()
{

}

void IEInteractionTrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IETrigger::Initialization(physicEdge, physicNodeType, clockType, param);

	SetAllowStrikeRepeat(true);
}

IEInteractionTrigger * IEInteractionTrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IEInteractionTrigger * trigger = new IEInteractionTrigger();
	trigger->Initialization(physicEdge, physicNodeType, clockType, param);
	return trigger;
}

void IEInteractionTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END