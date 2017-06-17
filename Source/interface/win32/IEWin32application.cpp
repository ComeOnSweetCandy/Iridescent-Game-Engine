#define __IE_DLL_EXPORTS__
#include "IEWin32application.h"
#include "../../tools/IEtime.h"

IE_BEGIN

IEWin32Application * IEWin32Application::m_StaticApplication = NULL;
IEWin32Application::IEWin32Application()
{
	m_scene = NULL;
	ran = 0.0f;
}

IEWin32Application::~IEWin32Application()
{
	//IEPhysicWorld::Share()->Release();
	//if (m_scene) m_scene->Release();
	////IEPathAnticipate::Share()->Release();
	//IEInputManager::Share()->Release();
	//IETime::Share()->Release();
	//IECamera::Share()->Release();
	//IEAutoReleasePool::Share()->Release();
	//RESOURCESDICTIONARYPOI->Release();
}

IEWin32Application * IEWin32Application::Share()
{
	if (m_StaticApplication == NULL)
	{
		m_StaticApplication = new IEWin32Application();
		m_StaticApplication->Initialization();
	}
	return m_StaticApplication;
}

void IEWin32Application::Initialization()
{
	DefaultSetup();
}

void IEWin32Application::Release()
{
	delete this;
}

void IEWin32Application::LockFps(unsigned char fps)
{
	IETime::Share()->LockFps(fps);
}

void IEWin32Application::ApplyScene(IEScene * scene)
{
	m_scene = scene;
	m_scene->Retain();
}

void IEWin32Application::DefaultSetup()
{
	//user defined begin this
	//.......................
	//user defined begin this
}

void IEWin32Application::LoopEnd()
{

}

void IEWin32Application::LoopBegin()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IEWin32Application::ApplicationLoop()
{
	LoopBegin();

	IETime::Share()->Run();
	IEInputManager::Share()->Run();
	IECamera::Share()->Run();
	if (m_scene)
	{
		m_scene->Visit();
	}
	LoopEnd();
	IEAutoReleasePool::Share()->Run();
}

IE_END