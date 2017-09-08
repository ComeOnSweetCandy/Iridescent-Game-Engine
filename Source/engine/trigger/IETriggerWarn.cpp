#define __IE_DLL_EXPORTS__
#include "IETriggerWarn.h"

IE_BEGIN

IETriggerWarn::IETriggerWarn()
{
	m_triggerType = __trigger_warn_type__;
}

IETriggerWarn::~IETriggerWarn()
{

}

void IETriggerWarn::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger::Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IETriggerWarn * IETriggerWarn::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETriggerWarn * trigger = new IETriggerWarn();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IETriggerWarn::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END