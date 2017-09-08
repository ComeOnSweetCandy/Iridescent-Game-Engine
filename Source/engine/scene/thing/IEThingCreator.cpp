#define __IE_DLL_EXPORTS__
#include "IEThingCreator.h"

#include "IEThingList.h"

#include "IEThingDirection.h"
#include "IEThingLine.h"
#include "IEThingJoint.h"

#include "items/IETorch.h"
#include "items/IEDoorInteraction.h"
#include "items/IEDoorInducation.h"

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

	if (thingType == 1)
	{
		//����ͨ���͵�thing
		return IEThing::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 2)
	{
		//��ͨ�ķ�������
		return IEThingDirection::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 3)
	{
		//��ͨ�ĺ�������
		return IEThingLine::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 4)
	{
		//��ͨ����������
		return IEThingJoint::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 11)
	{
		//torch��
		return IETorch::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 21)
	{
		//��Ӧ����
		return IEDoorInducation::Create(thingType, thingID, thingOrder);
	}
	else if (thingType == 22)
	{
		//��������
		return IEDoorInteraction::Create(thingType, thingID, thingOrder);
	}
	else
	{
		return NULL;
		__IE_WARNING__("IEThingCreator : Function CreateThingByType error.\n");
	}
}

IE_END