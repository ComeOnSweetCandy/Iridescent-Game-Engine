#define __IE_DLL_EXPORTS__
#include "IEpropPack.h"
#include "../../ui/IEslot.h"

IE_BEGIN

IEPropPack::IEPropPack()
{
	m_packCapacity = 0;
	m_props = NULL;
}

IEPropPack::~IEPropPack()
{
	if (m_props)
	{
		delete []m_props;
	}
}

void IEPropPack::Initialization(IECreature * creature, unsigned int packCapacity)
{
	IEObject::Initialization();

	SetPackOwner(creature);
	SetPackCapacity(packCapacity);
}

IEPropPack * IEPropPack::Create(IECreature * creature, unsigned int packCapacity)
{
	IEPropPack * propPack = new IEPropPack();
	propPack->Initialization(creature, packCapacity);
	return propPack;
}

void IEPropPack::AddProp(IEProp * prop)
{
	int propID = prop->GetPropID();
	int propCount = prop->GetPropCount();
	unsigned int leftNumber = 0;

	unsigned int emptyIndex = -1;
	for (unsigned int index = 0; index < m_packCapacity; index++)
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
			if (m_props[index]->GetPropID() == propID)
			{
				leftNumber = m_props[index]->AddPropCount(propCount);
				if (leftNumber != 0)
				{
					//没有全部放入 接着放
				}
				else
				{
					//放完了 返回
					UpdateUI();
					return;
				}
			}
		}
	}

	if (emptyIndex == -1)
	{

	}
	else
	{
		//IEPropType propType = prop->GetPropType();
		//if (propType == __prop_picked_type__)
		//{
		//	IEUsedProp * usedProp = IEUsedProp::Create(propIndex, propCount);
		//	m_props[emptyIndex] = usedProp;
		//	m_props[emptyIndex]->SetPropPack(this);
		//	m_props[emptyIndex]->SetPropOwner(m_packOwner);
		//}
		//else if (propType == __prop_used_type__)
		//{
		//	m_props[emptyIndex] = (IEUsedProp *)prop;
		//}
	}

	UpdateUI();
	return;
}

void IEPropPack::DropProp(unsigned int packIndex)
{
	if (m_props[packIndex])
	{
		m_props[packIndex] = NULL;

		UpdateUI();
	}
}

void IEPropPack::UseProp(unsigned int packIndex)
{
	if (m_props[packIndex])
	{
		m_props[packIndex]->UseProp();

		UpdateUI();
	}
}

void IEPropPack::UpdateUI()
{
	//if (!m_slot)
	//{
	//	//还没有UI
	//	return;
	//}

	//for (int index = 0; index < m_packCapacity; index++)
	//{
	//	if (m_props[index] != NULL)
	//	{
	//		m_slot->SetButton(index, m_props[index], m_props[index]->GetPropTexture("propIcon"), true);
	//	}
	//	else
	//	{
	//		m_slot->SetButton(index, NULL, NULL, true);
	//	}
	//}
}

void IEPropPack::SetSlot(IESlot * slot)
{
	m_slot = slot;
}

void IEPropPack::SetPackCapacity(unsigned int packCapacity)
{
	m_packCapacity = packCapacity;

	if (m_props)
	{

	}
	else
	{
		m_props = new IEProp *[m_packCapacity];

		for (unsigned int index = 0; index < m_packCapacity; index++)
		{
			m_props[index] = NULL;
		}
	}
}

void IEPropPack::SetPackOwner(IECreature * creature)
{
	m_owner = creature;
}

IECreature * IEPropPack::GetPackOwner()
{
	return m_owner;
}

unsigned int IEPropPack::GetPackCapacity()
{
	return m_packCapacity;
}

IE_END