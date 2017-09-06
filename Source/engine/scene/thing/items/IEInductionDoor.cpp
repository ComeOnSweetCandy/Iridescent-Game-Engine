#define __IE_DLL_EXPORTS__
#include "IEInductionDoor.h"

#include "../IEthingArea.h"

#include "../../../../interface/cmd/IEapplication.h"

#include "../../../../physic/physicEdge/IEphysicCircle.h"
#include "../../../trigger/IEWarnTrigger.h"

IE_BEGIN

IEInductionDoor::IEInductionDoor()
{
	m_lastSwitch = false;
	m_switch = false;
}

IEInductionDoor::~IEInductionDoor()
{

}

void IEInductionDoor::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEInductionDoor * IEInductionDoor::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEInductionDoor * thing = new IEInductionDoor();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEInductionDoor::Live()
{
	if (m_switch != m_lastSwitch)
	{
		//跟上一次状态不一样 那么
		if (m_switch == true)
		{
			ChangeState("open");
			//m_physicNode->SetPhysicNodeType(__physic_air_node__);
		}
		else if (m_switch == false)
		{
			ChangeState("close");
			//m_physicNode->SetPhysicNodeType(__physic_static_node__);
		}
	}

	//这里应该设定一个 执行一次动画后 回调一个函数
	m_lastSwitch = m_switch;
	m_switch = false;
}

void IEInductionDoor::CheckAround(bool active)
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

void IEInductionDoor::TriggerStrike(IEPhysicNode * physicNode)
{
	//说明被触发了 这个时候转换状态
	m_switch = true;
}

void IEInductionDoor::BindTriggers()
{
	//读取触发器信息
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * physicXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");

	m_triggers = IEWarnTrigger::Create(physicXML, true, true);														//建立一个永久有效的warn触发器
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEInductionDoor::TriggerStrike));								//激活触发器
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);	//设定位置
}

void IEInductionDoor::RereadSelf()
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