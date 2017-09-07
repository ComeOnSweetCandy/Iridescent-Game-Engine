#define __IE_DLL_EXPORTS__
#include "IEInteraction.h"

#include "../IEthingArea.h"
#include "../../../trigger/IEinteractionTrigger.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEInteraction::IEInteraction()
{
	m_switch = false;
}

IEInteraction::~IEInteraction()
{

}

void IEInteraction::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEInteraction * IEInteraction::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEInteraction * thing = new IEInteraction();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEInteraction::CheckAround(bool active)
{
	//对四周进行检测
	static IEThingArea * area = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetThing();

	IEThing * grids[4];
	grids[0] = area->GetThing(m_locations[0], m_locations[1] - 1, m_locations[2], m_locations[3]);
	grids[1] = area->GetThing(m_locations[0] + 1, m_locations[1], m_locations[2], m_locations[3]);
	grids[2] = area->GetThing(m_locations[0], m_locations[1] + 1, m_locations[2], m_locations[3]);
	grids[3] = area->GetThing(m_locations[0] - 1, m_locations[1], m_locations[2], m_locations[3]);

	for (unsigned char index = 0; index < 4; index++)
	{
		m_round[index] = false;

		if (grids[index] && grids[index]->GetThingType() == 1)
		{
			m_round[index] = true;
		}
	}

	BindTriggers();
	RereadSelf();
}

void IEInteraction::Live()
{
	//do something
}

void IEInteraction::TriggerStrike(IEPhysicNode * physicNode)
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

void IEInteraction::BindTriggers()
{
	//读取触发器信息
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * physicXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");

	m_triggers = IEInteractionTrigger::Create(physicXML, true, true);												//建立一个永久有效的warn触发器
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEInteraction::TriggerStrike));								//激活触发器
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);	//设定位置
}

void IEInteraction::RereadSelf()
{
	//如果对边 为true
	//必须考虑门的方向 只有hr vr两种方向
	char finalGroupName[256];

	if (m_round[0] == true && m_round[2] == true && m_round[1] == false && m_round[3] == false)
	{
		sprintf(finalGroupName, "line_%d", 1);
	}
	else if (m_round[0] == false && m_round[2] == false && m_round[1] == true && m_round[3] == true)
	{
		sprintf(finalGroupName, "line_%d", 0);
	}
	else
	{
		sprintf(finalGroupName, "line_%d", 0);
		__IE_EDIT_DIALOG__("you can't add a door to such a place.\n");
	}

	ChangeState("close");
	ChangeGroup(finalGroupName, 1);
}

IE_END