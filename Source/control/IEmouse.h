/***********************************
* name     : IEmouse.h
* creater  : cosc
* info     : input mouse
* date     : 2016/12/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MOUSE__
#define __IE_MOUSE__

#include "IEinputPortocol.h"

IE_BEGIN

class __IE_DLL__ IEMouse :public IEInputPortocol
{
public:
	IEMouse();
	~IEMouse();
	virtual void Initialization(LPDIRECTINPUT8 m_pDI, HWND hwnd);
	static IEMouse * Share();

public:
	void Run();
	void ReckonMousePosition();
	BOOL IsButtonDown(int button);
	bool IsButtonTouch(int button);
	void GetMousePosition(int &x, int &y);
	bool IsMouseIn();

private:
	static IEMouse * m_StaticMouse;

	LPDIRECTINPUTDEVICE8 m_pDIDev;
	DIMOUSESTATE m_state;
	bool m_mouseIn;							//����Ƿ����
	bool m_buttonCache[2];

public:
	float _MousePositionX;
	float _MousePositionY;
	int _MouseLocationX;
	int _MouseLocationY;
	int _MouseTinyLocationX;
	int _MouseTinyLocationY;
};

IE_END

#endif