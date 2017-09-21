#define __IE_DLL_EXPORTS__
#include "IEPropEquipment.h"

IE_BEGIN

IEPropEquipment::IEPropEquipment()
{

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
	//装备该prop 针对不同类型的pro会产生不同的效果 由子类去处理
}

void IEPropEquipment::UseProp()
{
	//使用该prop 针对不同类型的prop会产生不同的效果 由子类去处理
}

void IEPropEquipment::PickProp(IECreature * creature)
{
	//拾取该prop 针对不同类型的prop会产生不同的效果 由子类去处理
	//IEPropEquipmentPack * bag = NULL;

	//bag->AddProp(this);
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