#define __IE_DLL_EXPORTS__
#include "IEdisplacement.h"

IE_BEGIN

IEDisplacement::IEDisplacement()
{
	m_actionType = __action_displacement__;
	m_actionLevel = __actionlevel_0__;
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
	GetActionNode();
}

IEDisplacement * IEDisplacement::Create()
{
	IEDisplacement * action = new IEDisplacement();
	action->Initialization(0, 0);
	return action;
}

IEDisplacement * IEDisplacement::Create(float x, float y)
{
	IEDisplacement * action = new IEDisplacement();
	action->Initialization(x, y);
	return action;
}

IEDisplacement * IEDisplacement::Create(int x, int y)
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

void IEDisplacement::SetDisplacement(float x, float y)
{
	m_displacement = IEVector((const float)x, (const float)y);
}

void IEDisplacement::SetDirection(int x, int y)
{
	m_direction = IEGrid(x, y);
}

IE_END