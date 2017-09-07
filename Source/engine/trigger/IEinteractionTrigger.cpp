#define __IE_DLL_EXPORTS__
#include "IEinteractionTrigger.h"

#include "../../control/IEkeyboard.h"

IE_BEGIN

IEInteractionTrigger::IEInteractionTrigger()
{
	m_triggerType = __trigger_interaction_type__;
}

IEInteractionTrigger::~IEInteractionTrigger()
{

}

void IEInteractionTrigger::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	//IETrigger::Initialization(physicEdge, physicNodeType, allowStrikeRepeat, allowStrikeRepeatByOne);
}

IEInteractionTrigger * IEInteractionTrigger::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IEInteractionTrigger * trigger = new IEInteractionTrigger();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

void IEInteractionTrigger::Collision(IEPhysicNode * physicNode)
{
	//检测是否按下了该按下的键
	if (IEKeyboard::Share()->KeyTouch(DIK_E))
	{
		IETrigger::Collision(physicNode);
	}
}

IE_END