#define __IE_DLL_EXPORTS__
#include "IEbesiegeTrigger.h"

IE_BEGIN

IEBesiegeTrigger::IEBesiegeTrigger()
{
	m_triggerType = __trigger_collision_type__;
}

IEBesiegeTrigger::~IEBesiegeTrigger()
{

}

void IEBesiegeTrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IETrigger::Initialization(physicEdge, physicNodeType, clockType, param);
}

IEBesiegeTrigger * IEBesiegeTrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IEBesiegeTrigger * trigger = new IEBesiegeTrigger();
	trigger->Initialization(physicEdge, physicNodeType, clockType, param);
	return trigger;
}

void IEBesiegeTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END