#define __IE_DLL_EXPORTS__
#include "IEPropPack.h"
#include "../../ui/IEslot.h"

#include "IEPropCreator.h"

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

void IEPropPack::Initialization(IEArmer * creature, unsigned int packCapacity)
{
	IEObject::Initialization();

	SetPackOwner(creature);
	SetPackCapacity(packCapacity);
}

IEPropPack * IEPropPack::Create(IEArmer * creature, unsigned int packCapacity)
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
				if (leftNumber == 0)
				{					
					//放完了 返回
					UpdateUI();
					return;
				}
				else
				{
					//没有全部放入 接着放
				}
			}
		}
	}

	if (emptyIndex == -1)
	{
		//说明满了

	}
	else
	{
		IEPropType propType = prop->GetPropType();

		IEProp * newProp = CreateProp(propID, __prop_state_pack__);
		m_props[emptyIndex] = newProp;
		m_props[emptyIndex]->AddPropCount(propCount);
		m_props[emptyIndex]->SetOwner(m_owner);
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

void IEPropPack::DropProp(IEProp * prop)
{
	unsigned int index = GetPropIndex(prop);
	DropProp(index);
}

void IEPropPack::UseProp(unsigned int packIndex)
{
	if (m_props[packIndex])
	{
		m_props[packIndex]->UseProp();

		UpdateUI();
	}
}

void IEPropPack::ChangePropIndex(IEProp * prop1, IEProp * prop2)
{
	if (prop1 == NULL && prop2 == NULL)
	{
		//两个都为空 返回
		return;
	}

	int index1 = GetPropIndex(prop1);
	int index2 = GetPropIndex(prop2);

	if (index1 > -1)
	{
		m_props[index1] = prop2;
	}
	if (index2 > -1)
	{
		m_props[index2] = prop1;
	}
}

int IEPropPack::GetPropIndex(IEProp * prop)
{
	if (prop == NULL)
	{
		return -1;
	}

	for (unsigned int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index] == prop)
		{
			return index;
		}
	}

	return -1;
}

void IEPropPack::UpdateUI()
{
	ListProp();

	if (!m_slot)
	{
		//还没有UI
		return;
	}

	for (unsigned int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index] != NULL)
		{
			//m_slot->SetButton(index, m_props[index], m_props[index]->GetPropTexture("propIcon"), true);
		}
		else
		{
			//m_slot->SetButton(index, NULL, NULL, true);
		}
	}
}

void IEPropPack::ListProp()
{
	system("cls");

	for (unsigned int index = 0; index < m_packCapacity; index++)
	{
		if (m_props[index])
		{
			printf("[%d] name : %d    number : %d\n",index, m_props[index]->GetPropID(), m_props[index]->GetPropCount());
		}
		else
		{
			printf("[%d] empty\n");
		}
	}
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

void IEPropPack::SetPackOwner(IEArmer * creature)
{
	m_owner = creature;
}

IEArmer * IEPropPack::GetPackOwner()
{
	return m_owner;
}

unsigned int IEPropPack::GetPackCapacity()
{
	return m_packCapacity;
}

IE_END