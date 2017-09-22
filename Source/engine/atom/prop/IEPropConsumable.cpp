#define __IE_DLL_EXPORTS__
#include "IEPropConsumable.h"

#include "../creature/IEArmer.h"

IE_BEGIN

IEPropConsumable::IEPropConsumable()
{
	m_pileMax = 120;
}

IEPropConsumable::~IEPropConsumable()
{

}

void IEPropConsumable::Initialization(unsigned int propID, IEPropState propState)
{
	IEProp::Initialization(propID, propState);

	IEPropConsumable::InitUnit();
}

IEPropConsumable * IEPropConsumable::Create(unsigned int propIndex, IEPropState propState)
{
	IEPropConsumable * prop = new IEPropConsumable();
	prop->Initialization(propIndex, propState);
	return prop;
}

void IEPropConsumable::EquipProp()
{
	//装备该prop 针对不同类型的pro会产生不同的效果 由子类去处理
}

void IEPropConsumable::UseProp()
{
	if (LUAFunctionAllocateFunction(m_LUA, "UserProp"))
	{
		//LUASetUserdate(m_LUA, "self", "IECreature.IECreature", this);
		lua_call(m_LUA, 0, 0);
	}

	m_propCount--;

	ArrangeInfo();
}

void IEPropConsumable::PickProp(IEArmer * creature)
{
	//拾取该prop 针对不同类型的prop会产生不同的效果 由子类去处理
	//IEPropEquipmentPack * bag = NULL;

	//bag->AddProp(this);
}

void IEPropConsumable::ArrangeInfo()
{
	if (m_propCount == 0)
	{
		if (m_propState == __prop_state_pick__)
		{
			RemoveFromParent();
		}
		else if (m_propState == __prop_state_pack__)
		{
			m_owner->GetPlayersPack()->DropProp(this);
		}
	}
}

void IEPropConsumable::InitUnit()
{

}

IE_END