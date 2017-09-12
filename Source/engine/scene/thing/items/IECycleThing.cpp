#define __IE_DLL_EXPORTS__
#include "IECycleThing.h"

#include "../IEthingArea.h"
#include "../../../trigger/IETriggerInteraction.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IECycleThing::IECycleThing()
{
	m_switch = false;
}

IECycleThing::~IECycleThing()
{

}

void IECycleThing::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IECycleThing * IECycleThing::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IECycleThing * thing = new IECycleThing();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IECycleThing::CheckThing(bool active)
{
	IEThingLine::CheckThing(active);

	if (active)
	{
		BindTriggers();
	}
}

void IECycleThing::Live()
{
	//do something
}

void IECycleThing::TriggerStrike(IEPhysicNode * physicNode)
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

void IECycleThing::BindTriggers()
{
	//读取触发器信息
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * triggerXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");
	int triggerType = _xml->FindChild("property")->FindChild("trigger")->FindChild("triggetType")->ValueInt();

	m_triggers = IETriggerInteraction::Create(triggerXML, true, true);													//建立一个永久有效的warn触发器
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IECycleThing::TriggerStrike));								//激活触发器
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);		//设定位置
}

IE_END