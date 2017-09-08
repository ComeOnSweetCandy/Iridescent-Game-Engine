#define __IE_DLL_EXPORTS__
#include "IEThingLine.h"

#include "IEThingList.h"
#include "IEthingArea.h"

#include "../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEThingLine::IEThingLine()
{
	__IE_INIT_ARRAY__(m_round, 4, false);
}

IEThingLine::~IEThingLine()
{

}

void IEThingLine::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEThingLine * IEThingLine::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThingLine * thing = new IEThingLine();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEThingLine::CheckThing(bool active)
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

	RereadSelf();
}

void IEThingLine::RereadSelf()
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

	//更改为正确的状态
	ChangeGroup(finalGroupName, 1);
}

IE_END