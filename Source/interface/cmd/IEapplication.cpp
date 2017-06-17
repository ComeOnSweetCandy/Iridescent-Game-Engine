#define __IE_DLL_EXPORTS__
#include "IEapplication.h"
#include "IEframe.h"

IE_BEGIN

IEApplication * IEApplication::m_StaticApplication = NULL;

IEApplication::IEApplication()
{
	m_activeScene = NULL;
	m_uiScene = NULL;
	m_resourcesManger = NULL;
}

IEApplication::~IEApplication()
{
	__IE_RELEASE__(m_drawScene);
	__IE_RELEASE__(m_activeScene);
	__IE_RELEASE__(m_uiScene);
	__IE_RELEASE__(m_resourcesManger);

	IEFrame::Share()->Release();
}

IEApplication * IEApplication::Share()
{
	if (m_StaticApplication == NULL)
	{
		m_StaticApplication = new IEApplication();
		m_StaticApplication->Initialization();
	}
	return m_StaticApplication;
}

void IEApplication::Initialization()
{
	m_uiScene = IEUiScene::CreateAndRetain();
	m_drawScene = IEDrawScene::CreateAndRetain();
	m_resourcesManger = IEResourcesManager::CreateAndRetain();
}

void IEApplication::Release()
{
	delete this;
}

void IEApplication::ApplyScene(IETotalScene * scene)
{
	m_activeScene = scene;
}

IETotalScene * IEApplication::GetCurrentActiveScene()
{
	return m_activeScene;
}

IEUiScene * IEApplication::GetCurrentUIScene()
{
	return m_uiScene;
}

IEDrawScene * IEApplication::GetCurrentDrawScene()
{
	return m_drawScene;
}

void IEApplication::Run(int &argc, char *argv[])
{
	IEFrame::Share()->CreateOpenglWindow(argc, argv);
}

void IEApplication::LoopBegin()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IEApplication::ApplicationLoop()
{
	LoopBegin();

	__IE_RUN__(m_resourcesManger);
	__IE_RUN__(m_activeScene);
	__IE_RUN__(m_uiScene);
	__IE_RUN__(m_drawScene);

	LoopEnd();
}

void IEApplication::LoopEnd()
{

}

IE_END