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
		//首先获取贴图的名称 及贴图的序号

		//然后根据贴图名 获取到每帧的插入点及角度 
		float x, y, angle;
		bool res = GetWeaponPosition(m_textureUnit->_GroupName, m_textureUnit->_FrapIndex, x, y, angle);

		//然后根据返回的值，来改变weapon的坐标
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
		//更换
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
		//更换
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

	//首先 如果不存在 相应的绑定序列 则不显示weapon
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
			//如果有完整的序列绑定 那么正常显示
			x = arrays[frapIndex * 3]->transToFloat();
			y = arrays[frapIndex * 3 + 1]->transToFloat();
			angle = arrays[frapIndex * 3 + 2]->transToFloat();
		}
		else
		{
			//如果存在绑定序列 但是序号无法匹配 则总是匹配序列0
			x = arrays[0]->transToFloat();
			y = arrays[1]->transToFloat();
			angle = arrays[2]->transToFloat();
		}

		return true;
	}
}

IE_END