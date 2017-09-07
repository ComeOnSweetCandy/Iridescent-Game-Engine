#define __IE_DLL_EXPORTS__
#include "IEThingCreator.h"

#include "../IEThingList.h"
#include "IEJoint.h"
#include "IEInductionDoor.h"
#include "IEInteraction.h"

IE_BEGIN

IEThingEntry * entrys = IEThingList::Share()->GetEntrys();

IEThing * CreateThing(unsigned int thingID, unsigned int thingOrder)
{
	IEThing * newThing = CreateThingByType(thingID, thingOrder);

	return newThing;
}

IEThing * CreateThingByType(unsigned int thingID, unsigned int thingOrder)
{
	unsigned int thingType = entrys[thingID]._XML->FindChild("property")->FindChild("thingType")->ValueInt();

	if (thingType == 0)
	{
		//最普通类型的thing
		return IEThing::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 1)
	{
		return IEJoint::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 2)
	{
		return IEInductionDoor::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 3)
	{
		return IEInteraction::Create(thingType, thingID, thingOrder);
	}
	else
	{
		return NULL;
		__IE_WARNING__("IEThingCreator : Function CreateThingByType error.\n");
	}
}

IE_END