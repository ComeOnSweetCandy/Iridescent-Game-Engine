#define __IE_DLL_EXPORTS__
#include "IETriggerInteraction.h"

#include "../../control/IEkeyboard.h"

IE_BEGIN

IETriggerInteraction::IETriggerInteraction()
{
	m_triggerType = __trigger_interaction_type__;
}

IETriggerInteraction::~IETriggerInteraction()
{

}

void IETriggerInteraction::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger::Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IETriggerInteraction * IETriggerInteraction::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETriggerInteraction * trigger = new IETriggerInteraction();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IETriggerInteraction::Collision(IEPhysicNode * physicNode)
{
	//检测是否按下了该按下的键
	if (IEKeyboard::Share()->KeyTouch(DIK_E))
	{
		IETrigger::Collision(physicNode);
	}
}

IE_END