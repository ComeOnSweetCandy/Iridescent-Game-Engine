#define __IE_DLL_EXPORTS__
#include "IEArmer.h"

IE_BEGIN

IEArmer::IEArmer()
{
	m_propPack = IEPropPack::Create(this, 10);
}

IEArmer::~IEArmer()
{
	if (m_propPack)
	{
		m_propPack->ReleaseDisreference();
	}
}

void IEArmer::Initialization(unsigned int creatureID, unsigned int creatureOrder)
{
	IECreature::Initialization(creatureID, creatureOrder);

	//__prop_state_pack__
	//m_weapon = IEPropEquipment::Create(1,__prop_state_pick__);
}

IEArmer * IEArmer::Create(unsigned int creatureID, unsigned int creatureOrder)
{
	IEArmer * creature = new IEArmer();
	creature->Initialization(creatureID, creatureOrder);
	return creature;
}

void IEArmer::Update()
{
	IECreature::Update();

	DrawWeapon();
}

IEPropPack * IEArmer::GetPlayersPack()
{
	return m_propPack;
}

void IEArmer::DrawWeapon()
{
	if (m_weapon)
	{
		//���Ȼ�ȡ��ͼ������ ����ͼ�����

		//Ȼ�������ͼ�� ��ȡ��ÿ֡�Ĳ���㼰�Ƕ� 
		float x, y, angle;
		bool res = GetWeaponPosition(m_textureUnit->_GroupName, m_textureUnit->_FrapIndex, x, y, angle);

		//Ȼ����ݷ��ص�ֵ�����ı�weapon������
		if (res)
		{
			m_weapon->SetTranslate(x, y);
			m_weapon->SetRotate(angle);

			if (m_drawReverse)
			{
				m_weapon->Visit();
			}
			else
			{
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glTranslatef(m_size[0], 0.0f, 0.0f);
				glScalef(-1.0f, 1.0f, 1.0);
				m_weapon->Visit();
				glPopMatrix();
			}
		}
	}
}

void IEArmer::ArmEquipment(IEPropEquipment * equipment)
{
	IEPropEquipmentType equipmentType = equipment->GetEquipementType();

	switch (equipmentType)
	{
	case IridescentEngine::__prop_equipment_type_weapon__:
		ArmWeapon(equipment);
		break;
	case IridescentEngine::__prop_equipment_type_head__:
		ArmHead(equipment);
		break;
	default:
		break;
	}
}

void IEArmer::ArmWeapon(IEPropEquipment * equipment)
{
	if (m_weapon)
	{
		//����
		m_propPack->ChangePropIndex(equipment, m_weapon);
	}
	else
	{
		m_propPack->ChangePropIndex(equipment, NULL);
	}

	m_weapon = equipment;
}

void IEArmer::ArmHead(IEPropEquipment * equipment)
{
	if (m_weapon)
	{
		//����
		m_propPack->ChangePropIndex(equipment, m_weapon);
	}
	else
	{
		m_propPack->ChangePropIndex(equipment, NULL);
	}

	m_head = equipment;
}

bool IEArmer::GetWeaponPosition(const char * actionName, unsigned int frapIndex, float& x, float& y, float& angle)
{
	IEXml * bindingXML = m_XML->FindChild("binding")->FindChild(actionName);

	//���� ��������� ��Ӧ�İ����� ����ʾweapon
	if (bindingXML == NULL)
	{
		m_weapon->SetDisplay(false);
		return false;
	}
	else
	{
		m_weapon->SetDirection(true);

		IEString * infos = bindingXML->Value();
		IEContainer * container = infos->SplitBy(',');
		IEString ** arrays = (IEString **)(container->GetContainer());
		unsigned int m_vertexsNum = container->Count() / 3;

		if (m_vertexsNum > frapIndex)
		{
			//��������������а� ��ô������ʾ
			x = arrays[frapIndex * 3]->transToFloat();
			y = arrays[frapIndex * 3 + 1]->transToFloat();
			angle = arrays[frapIndex * 3 + 2]->transToFloat();
		}
		else
		{
			//������ڰ����� ��������޷�ƥ�� ������ƥ������0
			x = arrays[0]->transToFloat();
			y = arrays[1]->transToFloat();
			angle = arrays[2]->transToFloat();
		}

		return true;
	}
}

IE_END