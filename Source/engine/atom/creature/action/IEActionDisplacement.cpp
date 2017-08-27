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
	m_displace[0] = x;
	m_displace[1] = y;
	m_valueType = 0;
}

void IEDisplacement::Initialization(int x, int y)
{
	m_direction[0] = x;
	m_direction[1] = y;
	m_valueType = 1;
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
		//通过直接传递位移的值
		float abs_x = __IE_ABS__(m_displace[0]);
		float abs_y = __IE_ABS__(m_displace[1]);

		if (m_displace[0] > 0.0f)
		{
			if (abs_x >= abs_y)
			{
				m_direction[0] = 1;
				m_direction[1] = 0;
			}
		}
		else
		{
			if (abs_x >= abs_y)
			{
				m_direction[0] = -1;
				m_direction[1] = 0;
			}
		}
		
		if (m_displace[1] > 0.0f)
		{
			m_direction[0] = 0;
			m_direction[1] = 1;
		}
		else if (m_displace[1] < 0.0f)
		{
			m_direction[0] = 0;
			m_direction[1] = -1;
		}
	}

	//修改贴图组
	GetCreature()->ChangeGroup("walk", 1);

	//检测是否需要修改方向
	int * lastDirection = GetCreature()->GetDirection();
	if (lastDirection[0] == m_direction[0] && lastDirection[1] == m_direction[1])
	{
		//与上一次方向相同 无需更换贴图组
	}
	else
	{
		GetCreature()->SetDrawDirection(m_direction[0] >= 0 ? true : false, true);

		lastDirection[0] = m_direction[0];
		lastDirection[1] = m_direction[1];
	}

	if (m_valueType == 1)
	{
		//通过传递方向
		unsigned int speed = GetCreature()->GetCreatureUnit()->_Speed;
		float shift = (float)(speed) / 360 / 60;

		m_displace[0] = lastDirection[0];
		m_displace[1] = lastDirection[1];

		float _sqrt = sqrt(m_displace[0] * m_displace[0] + m_displace[1] * m_displace[1]);
		m_displace[0] = m_displace[0] / _sqrt * shift;
		m_displace[1] = m_displace[1] / _sqrt * shift;
	}
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