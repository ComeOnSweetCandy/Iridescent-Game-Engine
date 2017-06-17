/***********************************
* name     : IEapplication.h
* creater  : cosc
* info     : unique application enter
* date	   : 2016/11/18
* version  : 1.0
* remark   : none
************************************/
#ifndef __IE_WIN32_APPLICATION__
#define __IE_WIN32_APPLICATION__

#include "../../global/IEstdafx.h"
#include "../../core/container/IEautoReleasePool.h"
#include "../../core/container/IEdictionary.h"
#include "../../core/IEscene.h"
#include "../../control/IEinputManager.h"
#include "../../core/IEcamera.h"
#include "../../physic/IEphysicWorld.h"

IE_BEGIN

class __IE_DLL__ IEWin32Application
{
public:
	IEWin32Application();
	~IEWin32Application();
	static IEWin32Application * Share();
	void Initialization();
	void Release();

public:
	virtual void DefaultSetup();
	virtual void LoopEnd();
	void LockFps(unsigned char fps);
	void ApplyScene(IEScene * scene);
	void ApplicationLoop();
	void LoopBegin();

protected:
	static IEWin32Application * m_StaticApplication;

private:
	IEScene * m_scene;

public:
	float ran;
};

IE_END

#endif