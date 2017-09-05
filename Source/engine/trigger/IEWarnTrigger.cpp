#define __IE_DLL_EXPORTS__
#include "IEWarnTrigger.h"

IE_BEGIN

IEWarnTrigger::IEWarnTrigger()
{
	m_triggerType = __trigger_warn_type__;
}

IEWarnTrigger::~IEWarnTrigger()
{

}

void IEWarnTrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger::Initialization(physicEdge, physicNodeType, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IEWarnTrigger * IEWarnTrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IEWarnTrigger * trigger = new IEWarnTrigger();
	trigger->Initialization(physicEdge, physicNodeType, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IEWarnTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END