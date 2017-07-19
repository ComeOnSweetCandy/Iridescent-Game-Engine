/***********************************
* name     : IEvar.h
* creater  : cosc
* info     : base defined
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SITUATION__
#define __IE_SITUATION__

#include "IEvar.h"
#include "IEinclude.h"

class __IE_DLL__ IESituation
{
public:
	IESituation();
	~IESituation();
	static IESituation * Share();
	void Release();

public:
	static IESituation * m_StaticSituation;
	HWND _Hwnd;

	int _ScreenWidth;
	int _ScreenHeight;

	float _FieldAltitude;
};

#endif