#define __IE_DLL_EXPORTS__
#include "IEThingDirection.h"

#include "IEThingList.h"
#include "IEthingArea.h"

#include "../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEThingDirection::IEThingDirection()
{

}

IEThingDirection::~IEThingDirection()
{

}

void IEThingDirection::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEThingDirection * IEThingDirection::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThingDirection * thing = new IEThingDirection();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEThingDirection::CheckThing(bool active)
{
	//根据自身的方向值 来改变贴图
	char finalGroupName[256];

	if (m_direction == 0)
	{
		sprintf(finalGroupName, "S");
	}
	else if (m_direction == 2)
	{
		sprintf(finalGroupName, "E");
	}
	else if (m_direction == 4)
	{
		sprintf(finalGroupName, "N");
	}
	else if (m_direction == 6)
	{
		sprintf(finalGroupName, "W");
	}

	//更改为正确的状态
	ChangeGroup(finalGroupName, 1);
}

IE_END