#define __IE_DLL_EXPORTS__
#include "IEinputManager.h"

IE_BEGIN

IEInputManager * IEInputManager::m_StaticInputManager = NULL;

IEInputManager::IEInputManager()
{
	m_keyboardDev = NULL;
	m_mouseDev = NULL;
}

IEInputManager::~IEInputManager()
{
	if (m_keyboardDev) delete m_keyboardDev;
	if (m_mouseDev) delete m_mouseDev;
}

void IEInputManager::Initialization()
{
	m_hwnd = WindowFromDC(wglGetCurrentDC());
	HINSTANCE hInstance = GetModuleHandle(NULL);
	m_flags = false;

	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pdi, NULL)))
	{
		printf("direct input 8 create faild.\n");
	}
	if (!m_flags)
	{
		m_keyboardDev = IEKeyboard::Share();
		m_keyboardDev->Initialization(m_pdi, m_hwnd);
	}
	if (!m_flags)
	{
		m_mouseDev = IEMouse::Share();
		m_mouseDev->Initialization(m_pdi, m_hwnd);
	}
	m_flags = true;
}

void IEInputManager::Release()
{
	delete this;
}

IEInputManager * IEInputManager::Share()
{
	if (m_StaticInputManager == NULL)
	{
		m_StaticInputManager = new IEInputManager();
	}
	return m_StaticInputManager;
}

void IEInputManager::Run()
{
	if (!m_flags)
	{
		return;
	}
	if (m_keyboardDev) m_keyboardDev->Run();
	if (m_mouseDev)    m_mouseDev->Run();
}

IE_END