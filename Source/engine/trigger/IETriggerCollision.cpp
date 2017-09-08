#define __IE_DLL_EXPORTS__
#include "IETriggerCollision.h"

IE_BEGIN

IETriggerCollision::IETriggerCollision()
{
	m_triggerType = __trigger_collision_type__;
}

IETriggerCollision::~IETriggerCollision()
{

}

void IETriggerCollision::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger::Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IETriggerCollision * IETriggerCollision::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETriggerCollision * trigger = new IETriggerCollision();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IETriggerCollision::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END