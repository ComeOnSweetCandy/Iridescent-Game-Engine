/***********************************
* name     : IEapplication.h
* creater  : cosc
* info     : unique application enter
* date	   : 2016/11/18
* version  : 1.0
* remark   : none
************************************/
#ifndef __IE_APPLICATION__
#define __IE_APPLICATION__

#include "../../global/IEstdafx.h"

#include "../../core/container/IEautoReleasePool.h"
#include "../../core/container/IEdictionary.h"

#include "../../engine/scene/IEtotalScene.h"
#include "../../engine/ui/IEuiScene.h"
#include "../../engine/scene/IEdrawScene.h"
#include "../../engine/IEresourcesManager.h"

IE_BEGIN

#define __IE_RUN__(__p__)\
if (__p__)\
{\
	__p__->Run(); \
}

class IEFrame;

class __IE_DLL__ IEApplication
{
public:
	IEApplication();
	virtual ~IEApplication();
	virtual void Initialization();
	virtual void Release();
	static IEApplication * Share();

public:
	void ApplyScene(IETotalScene * scene);
	void Run(int &argc, char *argv[]);

	IETotalScene * GetCurrentActiveScene();
	IEUiScene * GetCurrentUIScene();
	IEDrawScene * GetCurrentDrawScene();

	virtual void DefaultSetup(){};
	virtual void ApplicationLoop();
	virtual void LoopBegin();
	virtual void LoopEnd();

protected:
	static IEApplication * m_StaticApplication;

private:
	IETotalScene * m_activeScene;				//当前活动场景
	IEDrawScene * m_drawScene;					//延迟渲染 基于z轴索引按序渲染
	IEUiScene * m_uiScene;						//UI场景渲染
	IEResourcesManager * m_resourcesManger;		//资源管理器
};

IE_END

#endif