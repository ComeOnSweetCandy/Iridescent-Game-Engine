#define __IE_DLL_EXPORTS__
#include "IEDoor.h"

#include "../IEThingList.h"
#include "../IEthingArea.h"

#include "../../../../interface/cmd/IEapplication.h"

#include "../../../trigger/IEtrigger.h"
#include "../../../../physic/physicEdge/IEphysicCircle.h"
#include "../../../trigger/IEinteractionTrigger.h"

IE_BEGIN

IEDoor::IEDoor()
{
	m_switch = false;
}

IEDoor::~IEDoor()
{

}

void IEDoor::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEDoor * IEDoor::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEDoor * light = new IEDoor();
	light->Initialization(thingType, thingID, thingOrder);
	return light;
}

void IEDoor::Live()
{
	static bool lastSwitch = false;

	if (m_switch != lastSwitch)
	{
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

	lastSwitch = m_switch;
	m_switch = false;
}

void IEDoor::CallFinal()
{
	CheckAround();

	//设定触发器
	IEPhysicCircleInfo * in = new IEPhysicCircleInfo();
	in->m_physicEdgeType = __edge_circle__;
	in->m_radius = 1.5f;
	in->m_vertexsCount = 32;

	IEPhysicCircle * attackPhysicEdge = IEPhysicCircle::Create(in);
	m_triggers = IEInteractionTrigger::Create(attackPhysicEdge, __physic_air_node__, __clock_strike_times_type__, 0);
	m_triggers->AddTrigger(IETrggerStrike(&IEDoor::TriggerStrike), this);
}

void IEDoor::CheckAround()
{
	//对四周进行检测
	static IEThingArea * area = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetThing();

	bool around[4];
	IEThing * grids[4];
	grids[0] = area->GetThing(m_locations[0], m_locations[1] - 1, m_locations[2], m_locations[3]);
	grids[1] = area->GetThing(m_locations[0] + 1, m_locations[1], m_locations[2], m_locations[3]);
	grids[2] = area->GetThing(m_locations[0], m_locations[1] + 1, m_locations[2], m_locations[3]);
	grids[3] = area->GetThing(m_locations[0] - 1, m_locations[1], m_locations[2], m_locations[3]);

	for (unsigned char index = 0; index < 4; index++)
	{
		around[index] = false;

		if (grids[index] && grids[index]->GetThingType() == m_thingType)
		{
			around[index] = true;
		}
	}

	//如果对边 为true
	//必须考虑门的方向 只有hr vr两种方向
	char finalGroupName[256];

	if (around[0] == true && around[2] == true && around[1] == false && around[3] == false)
	{
		sprintf(finalGroupName, "line_%d", 1);
	}
	else if (around[0] == false && around[2] == false && around[1] == true && around[3] == true)
	{
		sprintf(finalGroupName, "line_%d", 0);
	}
	else
	{
		__IE_EDIT_DIALOG__("you can't add a door to such a place.\n");
	}
}

void IEDoor::TriggerStrike(IEPhysicNode * physicNode)
{
	//说明被触发了 这个时候转换状态
	m_switch = true;
}

IE_END