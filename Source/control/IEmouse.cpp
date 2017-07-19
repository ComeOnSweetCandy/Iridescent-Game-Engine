#define __IE_DLL_EXPORTS__
#include "IEmouse.h"

IE_BEGIN

IEMouse * IEMouse::m_StaticMouse = NULL;

IEMouse::IEMouse()
{

}

IEMouse::~IEMouse()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}

void IEMouse::Initialization(LPDIRECTINPUT8 m_pDI, HWND hwnd)
{
	if (FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
	{
		printf("Failed to set data format<keyboard>");
	}
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
	{
		printf("can't set data format");
	}
	if (FAILED(m_pDIDev->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		printf("faild!");
	}
	if (FAILED(m_pDIDev->Acquire()))
	{
		//do not worry about this.
	}
}

IEMouse * IEMouse::Share()
{
	if (m_StaticMouse == NULL)
	{
		m_StaticMouse = new IEMouse();
	}
	return m_StaticMouse;
}

void IEMouse::Run()
{
	ReckonMousePosition();

	m_state.rgbButtons[0] = 0;
	m_state.rgbButtons[1] = 0;
	m_state.rgbButtons[2] = 0;
	m_state.rgbButtons[3] = 0;

	if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
	{
		if (FAILED(m_pDIDev->Acquire()))
		{
			//printf("there is something error with mouse device.\n");
		}
		if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
		{
			//printf("there is something error with mouse device.\n");
		}
	}

	for (unsigned int index = 0; index < 2; index++)
	{
		if (!(m_state.rgbButtons[index] & 0x80))
		{
			m_buttonCache[index] = false;
		}
	}
}

void IEMouse::ReckonMousePosition()
{
	POINT mousePos;
	GetCursorPos(&mousePos);	

	ScreenToClient(IESituation::Share()->_Hwnd, &mousePos);

	//检测鼠标是否过界
	if (mousePos.x<0 || mousePos.x>IESituation::Share()->_ScreenWidth || mousePos.y<0 || mousePos.y>IESituation::Share()->_ScreenHeight)
	{
		m_mouseIn = false;
	}
	else
	{
		m_mouseIn = true;
	}

	//计算鼠标所指向的地方 按场景计算
	mousePos.x = mousePos.x < 0 ? 0 : mousePos.x;
	mousePos.y = mousePos.y < 0 ? 0 : mousePos.y;
	mousePos.x = mousePos.x > IESituation::Share()->_ScreenWidth ? IESituation::Share()->_ScreenWidth : mousePos.x;
	mousePos.y = mousePos.y > IESituation::Share()->_ScreenHeight ? IESituation::Share()->_ScreenHeight : mousePos.y;

	float base = IESituation::Share()->_ScreenHeight / IESituation::Share()->_FieldAltitude / 2;
	int mClientPx = mousePos.x;
	int mClientPy = IESituation::Share()->_ScreenHeight - mousePos.y;

	float glX = (float)mClientPx / base;
	float glY = (float)mClientPy / base;

	float glScreenX = IESituation::Share()->_ScreenWidth / base;
	float glScreenXhalf = glScreenX / 2;

	float finalX = glX - glScreenXhalf;
	float finalY = glY - IESituation::Share()->_FieldAltitude;

	_MousePositionX = finalX;
	_MousePositionY = finalY;

	//然后计算鼠标所指向的格子和小格子
	float revisePositionX = _MousePositionX;
	float revisePositionY = _MousePositionY;
	if (revisePositionX < 0.0f)
	{
		revisePositionX = revisePositionX - 1.0f;
	}
	if (revisePositionY < 0.0f)
	{
		revisePositionY = revisePositionY - 1.0f;
	}
	_MouseLocationX = (int)revisePositionX;
	_MouseLocationY = (int)revisePositionY;
}

BOOL IEMouse::IsButtonDown(int button)
{
	if (m_state.rgbButtons[button] & 0x80)
	{
		return true;
	}
	return false;
}

bool IEMouse::IsButtonTouch(int button)
{
	if (m_state.rgbButtons[button] & 0x80 && m_buttonCache[button] == false)
	{
		m_buttonCache[button] = true;
		return true;
	}
	return false;
}

void IEMouse::GetMousePosition(int &x, int &y)
{
	x = m_state.lX;
	y = m_state.lY;
}

bool IEMouse::IsMouseIn()
{
	return m_mouseIn;
}

IE_END