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

void IEInteractionTrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	//IETrigger::Initialization(physicEdge, physicNodeType, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IEInteractionTrigger * IEInteractionTrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IEInteractionTrigger * trigger = new IEInteractionTrigger();
	trigger->Initialization(physicEdge, physicNodeType, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IEInteractionTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END