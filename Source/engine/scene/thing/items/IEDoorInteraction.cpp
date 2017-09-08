#define __IE_DLL_EXPORTS__
#include "IEDoorInteraction.h"

#include "../IEthingArea.h"
#include "../../../trigger/IETriggerInteraction.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEDoorInteraction::IEDoorInteraction()
{
	m_switch = false;
}

IEDoorInteraction::~IEDoorInteraction()
{

}

void IEDoorInteraction::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEDoorInteraction * IEDoorInteraction::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEDoorInteraction * thing = new IEDoorInteraction();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEDoorInteraction::CheckThing(bool active)
{
	IEThingLine::CheckThing(active);

	if (active)
	{
		BindTriggers();
	}
}

void IEDoorInteraction::Live()
{
	//do something
}

void IEDoorInteraction::TriggerStrike(IEPhysicNode * physicNode)
{
	//说明被触发了 这个时候转换状态
	m_switch = !m_switch;

	//跟上一次状态不一样 那么
	if (m_switch == true)
	{
		ChangeState("open");
	}
	else if (m_switch == false)
	{
		ChangeState("close");
	}
}

void IEDoorInteraction::BindTriggers()
{
	//读取触发器信息
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * triggerXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");
	int triggerType = _xml->FindChild("property")->FindChild("trigger")->FindChild("triggetType")->ValueInt();

	m_triggers = IETriggerInteraction::Create(triggerXML, true, true);													//建立一个永久有效的warn触发器
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEDoorInteraction::TriggerStrike));								//激活触发器
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);		//设定位置
}

IE_END