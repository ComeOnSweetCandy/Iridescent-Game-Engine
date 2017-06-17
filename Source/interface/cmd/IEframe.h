/***********************************
* name     : IEframe.h
* creater  : cosc
* info     : display frame
* c_date   : 2016/11/18
* l_date   : 2016/11/18
* version  : 1.0
* remark   : none
************************************/
#ifndef __IE_FRAME__
#define __IE_FRAME__

#include "../../global/IEinclude.h"
#include "../../global/IEvar.h"

IE_BEGIN

class IEApplication;

class __IE_DLL__ IEFrame
{
public:
	IEFrame();
	~IEFrame();
	static IEFrame * Share();
	void Release();
	void Initialization();

public:
	void CreateOpenglWindow(int &argc, char *argv[]);
	void Setup();
	static void MainLoop();
	static void ChangeSize(int w, int h);
	static void TimerFunction(int value);
	static void KeyPressFunc(unsigned char key, int x, int y);

private:
	static IEFrame * m_StaticFrame;
};

IE_END

#endif