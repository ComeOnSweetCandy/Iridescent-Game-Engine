#define __IE_DLL_EXPORTS__
#include "IEPropEquipment.h"

#include "../creature/IEArmer.h"

IE_BEGIN

IEPropEquipment::IEPropEquipment()
{
	m_pileMax = 1;
	m_propCount = 1;
}

IEPropEquipment::~IEPropEquipment()
{

}

void IEPropEquipment::Initialization(unsigned int propID, IEPropState propState)
{
	IEProp::Initialization(propID, propState);

	IEPropEquipment::InitUnit();
}

IEPropEquipment * IEPropEquipment::Create(unsigned int propIndex, IEPropState propState)
{
	IEPropEquipment * prop = new IEPropEquipment();
	prop->Initialization(propIndex, propState);
	return prop;
}

void IEPropEquipment::EquipProp()
{
	
}

void IEPropEquipment::UseProp()
{
	//equip
	m_owner->ArmWeapon(this);

	//if (LUAFunctionAllocateFunction(m_LUA, "UserProp"))
	//{
	//	//LUASetUserdate(m_LUA, "self", "IECreature.IECreature", this);
	//	lua_call(m_LUA, 0, 0);
	//}
}

void IEPropEquipment::PickProp(IEArmer * creature)
{
	
}

void IEPropEquipment::ArrangeInfo()
{
	if (m_propCount == 0)
	{
		//DelSelf();
	}
}

void IEPropEquipment::InitUnit()
{

}

IE_END