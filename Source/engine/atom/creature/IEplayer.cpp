#define __IE_DLL_EXPORTS__
#include "IEplayer.h"

#include "../../../core/IEcamera.h"

#include "../prop/IEpickedProp.h"
#include "../../action/IEwalk.h"

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
	IEAtom::Live();

	//处理键盘按键
	if (m_moveDirection.m_x || m_moveDirection.m_y)
	{
		//IEVector moveDirection = m_moveDirection;
		//moveDirection.Normalize();
		//moveDirection = moveDirection * (m_unitInfo->_Speed) * IETime::Share()->GetLastFrapPassingTime();

		IEDisplacement * action = IEDisplacement::Create(m_moveDirection.m_x, m_moveDirection.m_y);
		m_actionMachine->ChangeAction(__action_displacement__, action);
	}

	//重置所有的操作
	ResetEverything();

	//执行动作
	m_actionMachine->ExcuteAction();

	//设置camera
	const float * translate = GetTranslate();
	IECamera::Share()->SetCameraPosi(translate[0], translate[1]);
}

void IEPlayer::BindPlayerControl()
{
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyW), this, DIK_W);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyA), this, DIK_A);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyS), this, DIK_S);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyD), this, DIK_D);
	IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyJ), this, DIK_J);

	for (int index = 0; index < 10; index++)
	{
		IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressNumberKey), this, DIK_1 + index);
	}
}

void IEPlayer::HandleKeyboard()
{
	//if (IECamera::Share()->ValidateCameraMode(IEPlayerDriverCameraMode))
	//{
	//	IECamera::Share()->SetCameraPosi(m_position + m_displacement);
	//}
}

void IEPlayer::ResetEverything()
{
	m_moveDirection = 0;
}

void IEPlayer::PlayerPressKeyW(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(0, 1);
	HandleKeyboard();
}

void IEPlayer::PlayerPressKeyA(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(-1, 0);
	HandleKeyboard();
}

void IEPlayer::PlayerPressKeyS(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(0, -1);
	HandleKeyboard();
}

void IEPlayer::PlayerPressKeyD(unsigned char key)
{
	m_moveDirection = m_moveDirection + IEGrid(1, 0);
	HandleKeyboard();
}

void IEPlayer::PlayerPressKeyJ(unsigned char key)
{
	HandleKeyboard();
}

void IEPlayer::PlayerPressNumberKey(unsigned char key)
{
	int packIndex = key - DIK_1;

	IEUseProp * useProp = IEUseProp::Create(packIndex);
	m_actionMachine->ChangeAction(__action_useProp__, useProp);

	HandleKeyboard();
}

IE_END