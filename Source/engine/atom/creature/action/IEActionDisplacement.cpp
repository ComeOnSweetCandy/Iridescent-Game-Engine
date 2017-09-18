#define __IE_DLL_EXPORTS__
#include "IEActionDisplacement.h"

#include "../IECreature.h"

IE_BEGIN

IEDisplacement::IEDisplacement()
{

}

IEDisplacement::~IEDisplacement()
{

}

void IEDisplacement::Initialization(float x, float y)
{
	m_valueType = 0;

	m_displace[0] = x;
	m_displace[1] = y;
}

void IEDisplacement::Initialization(int x, int y)
{
	m_valueType = 1;

	m_doubleDirection[0] = x;
	m_doubleDirection[1] = y;
}

IEDisplacement * IEDisplacement::Create(int x, int y)
{
	IEDisplacement * action = new IEDisplacement();
	action->Initialization(x, y);
	return action;
}

IEDisplacement * IEDisplacement::Create(float x, float y)
{
	IEDisplacement * action = new IEDisplacement();
	action->Initialization(x, y);
	return action;
}

void IEDisplacement::Begin()
{
	if (m_valueType == 0)
	{
		//ͨ��ֱ�Ӵ���λ�Ƶ�ֵ
		float abs_x = __IE_ABS__(m_displace[0]);
		float abs_y = __IE_ABS__(m_displace[1]);

		if (m_displace[0] > 0.0f)
		{
			if (abs_x >= abs_y)
			{
				m_doubleDirection[0] = 1;
				m_doubleDirection[1] = 0;
			}
		}
		else
		{
			if (abs_x >= abs_y)
			{
				m_doubleDirection[0] = -1;
				m_doubleDirection[1] = 0;
			}
		}
		
		if (m_displace[1] > 0.0f)
		{
			m_doubleDirection[0] = 0;
			m_doubleDirection[1] = 1;
		}
		else if (m_displace[1] < 0.0f)
		{
			m_doubleDirection[0] = 0;
			m_doubleDirection[1] = -1;
		}

		//��Ҫ��ȡ��ֵ����


	}
	else if (m_valueType == 1)
	{
		//ͨ�����ݷ���
		unsigned int speed = GetCreature()->GetCreatureUnit()->_Speed;
		float shift = (float)(speed) / 360 / 60;

		//��Ҫ��ȡ��ֵ����
		TranslateDirection(m_doubleDirection[0], m_doubleDirection[1], m_singleDirection);

		m_displace[0] = m_doubleDirection[0];
		m_displace[1] = m_doubleDirection[1];

		float _sqrt = sqrt(m_displace[0] * m_displace[0] + m_displace[1] * m_displace[1]);
		m_displace[0] = m_displace[0] / _sqrt * shift;
		m_displace[1] = m_displace[1] / _sqrt * shift;
	}

	//����Ƿ���Ҫ�޸���ͼ����
	if (m_singleDirection == GetCreature()->GetDirection())
	{
		//����һ�η�����ͬ ���������ͼ��
	}
	else
	{
		//�޸���ͼ��
		GetCreature()->SetDirection(m_singleDirection);
		GetCreature()->ChangeGroup("walk", 1);
	}
}

void TranslateDirection(int x, int y, int direction)
{
	//��Ҫһ�ַ�ʽ����������֮�����Ѹ�ٵ�ת��


}

void IEDisplacement::Excute()
{
	SetActionNodeDisplacement();

	GetActionMachine()->ChangeAction(NULL);
}

void IEDisplacement::End()
{

}

void IEDisplacement::SetActionNodeDisplacement()
{
	GetCreature()->GetPhysicNode()->SetDisplacement(m_displace[0], m_displace[1]);
}

IE_END