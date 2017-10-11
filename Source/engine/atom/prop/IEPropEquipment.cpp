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
	m_owner->ArmWeapon(this);
}

void IEPropEquipment::UseProp()
{
	//equip
	if (m_owner->GetArmedWeapon() == NULL)
	{
		//װ��
		m_owner->ArmWeapon(this);
	}
	else if (m_owner->GetArmedWeapon() == this)
	{
		if (m_propEquipmentType == __prop_equipment_type_weapon__)
		{

		}
		//if (LUAFunctionAllocateFunction(m_LUA, "UserProp"))
		//{
		//	//LUASetUserdate(m_LUA, "self", "IECreature.IECreature", this);
		//	lua_call(m_LUA, 0, 0);
		//}
	}
	else
	{
		//�л�
		m_owner->ArmWeapon(this);
	}
}

void IEPropEquipment::PickProp(IEArmer * creature)
{
	
}

IEPropEquipmentType IEPropEquipment::GetEquipementType()
{
	return m_propEquipmentType;
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
	//��ȡ��װ��������
	m_propEquipmentType = (IEPropEquipmentType)(m_XML->FindChild("property")->FindChild("equipmentType")->ValueInt());
}

IE_END