#define __IE_DLL_EXPORTS__
#include "IEdisplacement.h"

#include "../IECreature.h"

IE_BEGIN

IEDisplacement::IEDisplacement()
{
	m_displacement = IEVector(0.0f, 0.0f);
}

IEDisplacement::~IEDisplacement()
{

}

void IEDisplacement::Initialization(float x, float y)
{
	SetDisplacement(x, y);

	float abs_x = __IE_ABS__(x);
	float abs_y = __IE_ABS__(y);

	if (x > 0.0f)
	{
		if (abs_x >= abs_y)
		{
			SetDirection(1, 0);
		}
	}
	else
	{
		if (abs_x >= abs_y)
		{
			SetDirection(-1, 0);
		}
	}
	
	if (y > 0.0f)
	{
		SetDirection(0, 1);
	}
	else if (y < 0.0f)
	{
		SetDirection(0, -1);
	}
}

void IEDisplacement::Initialization(int x, int y)
{
	//检测是否需要修改group
	int * lastDirection = GetCreature()->GetDirection();
	if (lastDirection[0] == x && lastDirection[1] == y)
	{
		//与上一次方向相同 无需更换贴图组
	}
	else
	{
		//与上一次方向不同
		IEString groupName = "walk_";
		if (x == 1)
		{
			groupName << 'r';
		}
		else if (x == 0)
		{
			//什么也不做
		}
		else if (x == -1)
		{
			//贴图翻转
			//???
			groupName << 'r';
		}

		if (y == 1)
		{
			groupName << 'b';
		}
		else if (y == 0)
		{
			//什么也不做
		}
		else if (y == -1)
		{
			groupName << 't';
		}
		
		//GetCreature()->ChangeGroup(groupName.GetString(), 1);
	}
	lastDirection[0] = x;
	lastDirection[1] = y;

	unsigned int speed = GetCreature()->GetCreatureUnit()->_Speed;
	float shift = (float)(speed) / 360 / 60;

	m_displacement[0] = lastDirection[0];
	m_displacement[1] = lastDirection[1];

	m_displacement.Normalize();
	m_displacement = m_displacement * shift;
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

bool IEDisplacement::Begin()
{
	ChangeActionTexture("walk");
	DeleteOtherActions();

	return true;
}

bool IEDisplacement::Excute()
{
	SetActionNodeFaceDirection();
	SetActionNodeDisplacement();

	DeleteAction(m_actionType);
	return true;
}

bool IEDisplacement::End()
{
	return true;
}

void IEDisplacement::SetActionNodeDisplacement()
{
	m_displacement = m_displacement * 4.0f;
	GetActionNode()->GetPhysicNode()->SetDisplacement(m_displacement.m_x, m_displacement.m_y);
}

void IEDisplacement::SetActionNodeFaceDirection()
{
	//GetCreatureUnit()->SetFacer(m_direction.m_x, m_direction.m_y);
	GetActionNode()->SetDirection(m_direction.m_x, m_direction.m_y);

	SetTextureDirection();
}

void IEDisplacement::SetTextureDirection()
{
	GetActionNode()->SetScale(m_displacement.m_x >= 0.0f ? 1 : -1);
}

IE_END