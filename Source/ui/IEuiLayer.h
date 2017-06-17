/***********************************
* name     : IEuiLayer.h
* creater  : cosc
* info     : ui layer
* date     : 2016/12/5
* version  : 1.0
* remark   : ui layer . it will not be changed element size when user change the screen w&h
			 the most important thing which is diffent with usual layer is the ui layer's
			 width and height equals the pixels belong to screen's width and height
************************************/

#ifndef __IE_UI_LAYER__
#define __IE_UI_LAYER__

#include "../core/IElayer.h"
#include "IEwidget.h"

IE_BEGIN

class __IE_DLL__ IEUiLayer :public IEWidget, public IELayer
{
public:
	IEUiLayer();
	virtual ~IEUiLayer();
	virtual void Initialization();
	virtual void Release();
	static IEUiLayer * Create();

public:
	virtual void Run();

protected:
	virtual void Visit();
	virtual void ChangeModelMatrix();
	virtual void RevertModelMatrix();
	virtual void DrawNode();

protected:
	IEGrid m_screenSize;
};

IE_END

#endif