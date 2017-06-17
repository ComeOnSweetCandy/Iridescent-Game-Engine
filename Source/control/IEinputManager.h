/***********************************
* name     : IEinputManager.h
* creater  : cosc
* info     : input manager
* date     : 2016/12/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_INPUT_MANAGER__
#define __IE_INPUT_MANAGER__

#include "IEkeyboard.h"
#include "IEmouse.h"

IE_BEGIN

class __IE_DLL__ IEInputManager
{
public:
	IEInputManager();
	~IEInputManager();
	void Release();
	virtual void Initialization();
	static IEInputManager * Share();

public:
	void Run();

private:
	static IEInputManager * m_StaticInputManager;

	HWND m_hwnd;
	LPDIRECTINPUT8 m_pdi;
	DWORD m_flags;
	IEKeyboard * m_keyboardDev;
	IEMouse * m_mouseDev;
};

IE_END

#endif