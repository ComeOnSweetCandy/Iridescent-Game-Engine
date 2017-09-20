#define __IE_DLL_EXPORTS__
#include "IEArmer.h"

IE_BEGIN

IEArmer::IEArmer()
{

}

IEArmer::~IEArmer()
{

}

void IEArmer::Initialization(unsigned int creatureID, unsigned int creatureOrder)
{
	IECreature::Initialization(creatureID, creatureOrder);

	IEXml * xml = IEXml::Create("weapon.tex.xml");
	IEPackerTexture * texture = IEPackerTexture::Create(xml);
	m_wea = IESprite::Create("weapon.png");
	m_wea->ChangeTexture(texture);
	m_wea->ChangeGroup("default");
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

void IEArmer::DrawWeapon()
{
	//���Ȼ�ȡ��ͼ������ ����ͼ�����

	//Ȼ�������ͼ�� ��ȡ��ÿ֡�Ĳ���㼰�Ƕ� 
	float x, y, angle;
	bool res = GetWeaponPosition(m_textureUnit->_GroupName, m_textureUnit->_FrapIndex, x, y, angle);

	//Ȼ����ݷ��ص�ֵ�����ı�weapon������
	if (res)
	{
		m_wea->SetTranslate(x, y);
		m_wea->SetRotate(angle);
		m_wea->Visit();

		static int i = 0;
		printf("%f %f %f %d\n", x, y, angle, i++);
	}
}

bool IEArmer::GetWeaponPosition(const char * actionName, unsigned int frapIndex, float& x, float& y, float& angle)
{
	IEXml * bindingXML = m_XML->FindChild("binding")->FindChild(actionName);

	//���� ��������� ��Ӧ�İ����� ����ʾweapon
	if (bindingXML == NULL)
	{
		m_wea->SetDisplay(false);

		return false;
	}
	else
	{
		m_wea->SetDirection(true);

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