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

void IEWarnTrigger::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger::Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IEWarnTrigger * IEWarnTrigger::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IEWarnTrigger * trigger = new IEWarnTrigger();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IEWarnTrigger::Collision(IEPhysicNode * physicNode)
{
	IETrigger::Collision(physicNode);
}

IE_END