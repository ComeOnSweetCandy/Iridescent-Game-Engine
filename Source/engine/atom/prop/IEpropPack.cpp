#define __IE_DLL_EXPORTS__
#include "IEpropPack.h"
#include "../../ui/IEslot.h"

IE_BEGIN

IEPropPack::IEPropPack()
{
	m_packOccupy = 0;
	m_packCapacity = 0;
	m_props = NULL;
}

IEPropPack::~IEPropPack()
{
	if (m_props)
	{
		for (int index = 0; index < m_packCapacity; index++)
		{
			if (m_props[index])
			{
				m_props[index]->ClockTick();
			}
		}

		delete []m_props;
	}
}

void IEPropPack::Initialization(IECreature * creature, int packCapacity)
{
	SetPackOwner(creature);
	SetPackCapacity(packCapacity);
}

IEPropPack * IEPropPack::Create(IECreature * creature, int packCapacity)
{
	IEPropPack * propPack = new IEPropPack();
	propPack->Initialization(creature, packCapacity);
	return propPack;
}

IEPropPack * IEPropPack::CreateAndRetain(IECreature * creature, int packCapacity)
{
	IEPropPack * propPack = new IEPropPack();
	propPack->Initialization(creature, packCapacity);
	propPack->Retain();
	return propPack;
}

void IEPropPack::SetPackCapacity(int packCapacity)
{
	m_packCapacity = packCapacity;

	if (m_props)
	{

	}
	else
	{
		m_props = new IEUsedProp *[m_packCapacity];

		for (int index = 0; index < m_packCapacity; index++)
		{
			m_props[index] = NULL;
		}
	}
}

void IEPropPack::SetSlot(IESlot * slot)
{
	m_slot = slot;
}

void IEPropPack::InsertProp(IEProp * prop)
{
	int propIndex = prop->GetPropIndex();
	int propCount = prop->GetPropCount();

	int emptyIndex = -1;
	for (int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index] == NULL)
		{
			if (emptyIndex == -1)
			{
				emptyIndex = index;
			}
		}
		else
		{
			if (m_props[index]->GetPropIndex() == propIndex)
			{
				m_props[index]->AddPropCount(propCount);

				UpdateUI();
				return;
			}
		}
	}

	if (emptyIndex == -1)
	{

	}
	else
	{
		IEPropType propType = prop->GetPropType();
		if (propType == __prop_picked_type__)
		{
			IEUsedProp * usedProp = IEUsedProp::Create(propIndex, propCount);
			m_props[emptyIndex] = usedProp;
			m_props[emptyIndex]->SetPropPack(this);
			m_props[emptyIndex]->SetPropOwner(m_packOwner);
		}
		else if (propType == __prop_used_type__)
		{
			m_props[emptyIndex] = (IEUsedProp *)prop;
		}
	}

	UpdateUI();
	return;
}

void IEPropPack::DeleteProp(IEUsedProp * prop)
{
	int propIndex = prop->GetPropIndex();

	for (int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index] != NULL)
		{
			if (m_props[index]->GetPropIndex() == propIndex)
			{
				m_props[index]->ClockTick();
				m_props[index] = NULL;

				UpdateUI();
				return;
			}
		}
	}
}

void IEPropPack::DropProp(IEUsedProp * prop)
{

}

void IEPropPack::UseProp(int packIndex)
{
	if (m_props[packIndex] != NULL)
	{
		m_props[packIndex]->UseProp();

		UpdateUI();
		return;
	}
}

void IEPropPack::UpdateUI()
{
	if (!m_slot)
	{
		//»¹Ã»ÓÐUI
		return;
	}

	for (int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index] != NULL)
		{
			m_slot->SetButton(index, m_props[index], m_props[index]->GetPropTexture("propIcon"), true);
		}
		else
		{
			m_slot->SetButton(index, NULL, NULL, true);
		}
	}
}

bool IEPropPack::HaveProp(int packIndex)
{
	if (packIndex >= m_packCapacity)
	{
		return false;
	}
	if (m_props[packIndex])
	{
		return true;
	}
	return false;
}

void IEPropPack::SetPackOwner(IECreature * creature)
{
	m_packOwner = creature;
}

IECreature * IEPropPack::GetPackOwner()
{
	return m_packOwner;
}

IE_END