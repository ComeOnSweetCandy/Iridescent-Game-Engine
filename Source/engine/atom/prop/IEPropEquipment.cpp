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
	//װ����prop ��Բ�ͬ���͵�pro�������ͬ��Ч�� ������ȥ����
}

void IEPropEquipment::UseProp()
{
	//ʹ�ø�prop ��Բ�ͬ���͵�prop�������ͬ��Ч�� ������ȥ����
}

void IEPropEquipment::PickProp(IECreature * creature)
{
	//ʰȡ��prop ��Բ�ͬ���͵�prop�������ͬ��Ч�� ������ȥ����
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