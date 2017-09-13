#define __IE_DLL_EXPORTS__
#include "IECycleThing.h"

#include "../IEthingArea.h"
#include "../../../trigger/IETriggerInteraction.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IECycleThing::IECycleThing()
{
	
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
		BindClock();
	}
}

void IECycleThing::Live()
{
	//do something
}

void IECycleThing::TriggerStrike(IEPhysicNode * physicNode)
{
	//说明被触发了 这个时候转换状态
}

void IECycleThing::BindClock()
{

}

IE_END