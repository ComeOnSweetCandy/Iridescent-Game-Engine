#define __IE_DLL_EXPORTS__
#include "IEActionWalk.h"

#include "../IECreature.h"

IE_BEGIN

IEActionWalk::IEActionWalk()
{

}

IEActionWalk::~IEActionWalk()
{

}

void IEActionWalk::Initialization(float x, float y)
{
	m_valueType = 0;

	m_displace[0] = x;
	m_displace[1] = y;
}

void IEActionWalk::Initialization(int x, int y)
{
	m_valueType = 1;

	m_doubleDirection[0] = x;
	m_doubleDirection[1] = y;
}

IEActionWalk * IEActionWalk::Create(int x, int y)
{
	IEActionWalk * action = new IEActionWalk();
	action->Initialization(x, y);
	return action;
}

IEActionWalk * IEActionWalk::Create(float x, float y)
{
	IEActionWalk * action = new IEActionWalk();
	action->Initialization(x, y);
	return action;
}

//需要一种方式，能让两者之间进行迅速的转换
static int _DirectionArray[8][2] =
{
	{ 0, -1 },
	{ 1, -1 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 },
};

void TranslateDirectionDoubleToSingle(int& x, int& y, int& direction)
{
	for (int index = 0; index < 8; index++)
	{
		if (_DirectionArray[index][0] == x && _DirectionArray[index][1] == y)
		{
			direction = index;

			return;
		}
	}
}

void TranslateDirectionSingleToDouble(int& x, int& y, int& direction)
{
	direction = direction % 8;

	x = _DirectionArray[direction][0];
	y = _DirectionArray[direction][1];
}

void IEActionWalk::Begin()
{
	if (m_valueType == 0)
	{
		//通过直接传递位移的值
		m_doubleDirection[1] = 0;

		if (m_displace[0] >= 0.0f)
		{
			m_doubleDirection[0] = 1;
			m_singleDirection = 2;
		}
		else
		{
			m_doubleDirection[0] = -1;
			m_singleDirection = 6;
		}
	}
	else if (m_valueType == 1)
	{
		//通过传递方向
		unsigned int speed = GetCreature()->GetCreatureUnit()->_Speed;
		float shift = (float)(speed) / 360 / 60;

		//需要获取单值方向
		TranslateDirectionDoubleToSingle(m_doubleDirection[0], m_doubleDirection[1], m_singleDirection);

		m_displace[0] = m_doubleDirection[0];
		m_displace[1] = m_doubleDirection[1];

		float _sqrt = sqrt(m_displace[0] * m_displace[0] + m_displace[1] * m_displace[1]);
		m_displace[0] = m_displace[0] / _sqrt * shift;
		m_displace[1] = m_displace[1] / _sqrt * shift;
	}

	GetCreature()->SetDrawReverse(m_doubleDirection[0] > 0 ? true : false);
	GetCreature()->SetDirection(m_singleDirection);
	GetCreature()->ChangeGroup("walk", __creature_part_leg__);
}

void IEActionWalk::Excute()
{
	SetActionNodeDisplacement();

	GetActionMachine()->ChangeAction(NULL);
}

void IEActionWalk::End()
{
	//GetCreature()->ChangeGroup("stop", __creature_part_leg__);
}

void IEActionWalk::SetActionNodeDisplacement()
{
	GetCreature()->GetPhysicNode()->SetDisplacement(m_displace[0], m_displace[1]);
}

IE_END