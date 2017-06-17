#define __IE_DLL_EXPORTS__
#include "IEcollisionTrigger.h"

IE_BEGIN

IECollisionTrigger::IECollisionTrigger()
{
	m_triggerType = __trigger_collision_type__;
}

IECollisionTrigger::~IECollisionTrigger()
{

}

void IECollisionTrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IETrigger::Initialization(physicEdge, physicNodeType, clockType, param);
}

IECollisionTrigger * IECollisionTrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IECollisionTrigger * trigger = new IECollisionTrigger();
	trigger->Initialization(physicEdge, physicNodeType, clockType, param);
	return trigger;
}

void IECollisionTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END