#define __IE_DLL_EXPORTS__
#include "IEkeyboard.h"

IE_BEGIN

IEKeyboard * IEKeyboard::m_StaticKeyboard = NULL;

IEKeyboard::IEKeyboard()
{
	for (unsigned int index = 0; index < KEYBOARDCOUNT; index++)
	{
		m_keyboardBindList[index].m_node = NULL;
		m_keyboardBindList[index].m_keyboardCallback = NULL;
	}
}

IEKeyboard::~IEKeyboard()
{
	if (m_pDIDev)
	{
		m_pDIDev->Unacquire();
		m_pDIDev->Release();
	}
}

void IEKeyboard::Initialization(LPDIRECTINPUT8 m_pDI, HWND hwnd)
{
	if (FAILED(m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
	{
		printf("Failed to set data format<keyboard>");
	}
	if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
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

	ZeroMemory(m_keyboardString, KEYBOARDCOUNT);
}

IEKeyboard * IEKeyboard::Share()
{
	if (m_StaticKeyboard == NULL)
	{
		m_StaticKeyboard = new IEKeyboard();
	}
	return m_StaticKeyboard;
}

void IEKeyboard::Run()
{
	if (FAILED(m_pDIDev->GetDeviceState(KEYBOARDCOUNT, (LPVOID)m_keyboardString)))
	{
		if (FAILED(m_pDIDev->Acquire()))
		{
			//printf("there is something error with keyboard device.\n");
		}
		if (FAILED(m_pDIDev->GetDeviceState(KEYBOARDCOUNT, (LPVOID)m_keyboardString)))
		{
			//printf("there is something error with keyboard device.\n");
		}
	}

	//如果按下键 传递绑定消息
	for (unsigned int index = 0; index < KEYBOARDCOUNT; index++)
	{
		if (IsKeyDown(index))
		{
			if (IsUsingKeyboard(index))
			{
				(m_keyboardBindList[index].m_node->*(m_keyboardBindList[index].m_keyboardCallback))(index);
			}
		}
		else
		{
			m_keyboardCache[index] = false;
		}
	}
}

bool IEKeyboard::IsKeyDown(unsigned int key)
{
	if (m_keyboardString[key] & 0x80)
	{
		return true;
	}
	return false;
}

bool IEKeyboard::KeyTouch(unsigned int key)
{
	if ((m_keyboardString[key] & 0x80) && m_keyboardCache[key] == false)
	{
		m_keyboardCache[key] = true;
		return true;
	}
	return false;
}

void IEKeyboard::HandleKey(unsigned int & key)
{
	if (IsUsingKeyboard(key))
	{
		(m_keyboardBindList[key].m_node->*(m_keyboardBindList[key].m_keyboardCallback))(key);
	}
}

void IEKeyboard::UnbindKeyboardCallback(unsigned int key)
{
	if (IsUsingKeyboard(key))
	{
		m_keyboardBindList[key].m_node = NULL;
		m_keyboardBindList[key].m_keyboardCallback = NULL;
	}
	else
	{
		printf("this keyboard are not been using now\n");
	}
}

void IEKeyboard::BindKeyboardCallback(IEKeyboardCallback keyboardCallback, IENode * node, unsigned int key, bool deleteOlder)
{
	if (IsUsingKeyboard(key))
	{
		if (deleteOlder == false)
		{
			printf("this keyboard has been used\n");

			return;
		}
		else
		{

		}
	}

	m_keyboardBindList[key].m_node = node;
	m_keyboardBindList[key].m_keyboardCallback = keyboardCallback;
}

bool IEKeyboard::IsUsingKeyboard(unsigned int & key)
{
	if (m_keyboardBindList[key].m_node && m_keyboardBindList[key].m_keyboardCallback)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IE_END