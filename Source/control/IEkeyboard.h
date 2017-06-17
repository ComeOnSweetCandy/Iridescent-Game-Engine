/***********************************
* name     : IEkeyboard.h
* creater  : cosc
* info     : keyboard controller
* date     : 2016/12/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_KEYBOARD__
#define __IE_KEYBOARD__

#include "../global/IEstdafx.h"
#include "../core/IEobject.h"
#include "../core/IEnode.h"
#include "IEinputPortocol.h"

IE_BEGIN

#define KEYBOARDCOUNT 256

typedef struct ieKeyboardBindList
{
	IENode * m_node;
	IEKeyboardCallback m_keyboardCallback;
}IEKeyBoardBindList;

class __IE_DLL__ IEKeyboard
{
public:
	IEKeyboard();
	~IEKeyboard();
	virtual void Initialization(LPDIRECTINPUT8 m_pDI, HWND hwnd);
	static IEKeyboard * Share();
	
public:
	void Run();
	bool IsKeyDown(unsigned int key);
	bool KeyTouch(unsigned int key);
	bool KeyLeave(unsigned int key);
	void HandleKey(unsigned int & key);
	void UnbindKeyboardCallback(unsigned int key);
	void BindKeyboardCallback(IEKeyboardCallback keyboardCallback, IENode * node, unsigned int key, bool deleteOlder = false);
	bool IsUsingKeyboard(unsigned int & key);

private:
	static IEKeyboard * m_StaticKeyboard;

	IEKeyBoardBindList m_keyboardBindList[KEYBOARDCOUNT];
	LPDIRECTINPUTDEVICE8 m_pDIDev;
	char m_keyboardString[KEYBOARDCOUNT];
	bool m_keyboardCache[KEYBOARDCOUNT];
};

IE_END

#endif