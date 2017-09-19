#define __IE_DLL_EXPORTS__
#include "IEPlayer.h"

#include "../../../core/IEcamera.h"

#include "../prop/IEpickedProp.h"

#include "action/IEActionDisplacement.h"
#include "action/IEActionRest.h"
#include "action/IEActionAttack.h"

IE_BEGIN

IEPlayer::IEPlayer()
{
	m_moveDirection = 0;
	m_propPack = NULL;
}

IEPlayer::~IEPlayer()
{
	if (m_propPack)
	{
		m_propPack->Release();
	}
}

void IEPlayer::Initialization(int creatureID)
{
	IECreature::Initialization(creatureID, 0);

	m_propPack = IEPropPack::CreateAndRetain(this, 10);
	BindPlayerControl();

	//直接定义为用户
	_Unit->_Party = __creature_party_mine__;
	IECreature::User();
}

IEPlayer * IEPlayer::Create(int creatureIndex)
{
	IEPlayer * object = new IEPlayer();
	object->Initialization(creatureIndex);
	return object;
}

IEPropPack * IEPlayer::GetPlayersPack()
{
	return m_propPack;
}

void IEPlayer::Live()
{
	IECreature::Live();

	//处理用户操作
	HandlePlayerControll();

	//重置所有的操作
	ResetEverything();
}

void IEPlayer::HandlePlayerControll()
{
	//处理键盘按键
	m_nextAction = NULL;

	if (m_moveDirection.m_x || m_moveDirection.m_y)
	{
		m_nextAction = IEDisplacement::Create(m_moveDirection.m_x, m_moveDirection.m_y);
	}
	else if (m_attack)
	{
		m_nextAction = IEActionAttack::Create();
	}
	else
	{
		m_nextAction = IERest::Create();
	}

	if (IEKeyboard::Share()->KeyTouch(DIK_J))
	{
		//如果当前处于该状态
		//m_nextAction = IERest::Create();

		if (m_physicNode->GetPhysicState() == __physic_state_static__)
		{
			m_physicNode->SetForward(0, 20.0f);
		}
	}

	if (m_nextAction)
	{
		m_actionMachine->ChangeAction(m_nextAction);
	}
}

void IEPlayer::ResetEverything()
{
	m_moveDirection = 0;
	m_attack = false;
	m_jump = false;
}

void IEPlayer::BindPlayerControl()
{
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyA), this, DIK_A);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyD), this, DIK_D);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyJ), this, DIK_J);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyK), this, DIK_K);

	for (int index = 0; index < 10; index++)
	{
		IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressNumberKey), this, DIK_1 + index);
	}
}

void IEPlayer::PlayerPressKeyA(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(-1, 0);
}

void IEPlayer::PlayerPressKeyD(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(1, 0);
}

void IEPlayer::PlayerPressKeyJ(unsigned char key)
{
	m_jump = true;
}

void IEPlayer::PlayerPressKeyK(unsigned char key)
{
	m_attack = true;
}

void IEPlayer::PlayerPressNumberKey(unsigned char key)
{
	int packIndex = key - DIK_1;

	//IEUseProp * useProp = IEUseProp::Create(packIndex);
	//m_actionMachine->ChangeAction(__action_useProp__, useProp);
}

IE_END