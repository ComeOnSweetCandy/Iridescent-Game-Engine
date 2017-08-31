#define __IE_DLL_EXPORTS__
#include "IEDoor.h"

IE_BEGIN


IEDoor::IEDoor()
{

}

IEDoor::~IEDoor()
{

}

void IEDoor::Initialization(unsigned int thingID)
{
	IEThing::Initialization(thingID);

	//...
	m_XML;

	
}

IEDoor * IEDoor::Create(unsigned int thingID)
{
	IEDoor * light = new IEDoor();
	light->Initialization(thingID);
	return light;
}

void IEDoor::Update()
{
	//ºôÎüĞ§¹û

}

void IEDoor::ChangeState(unsigned int stateIndex)
{

}

IE_END