#define __IE_DLL_EXPORTS__
#include "IEtotalScene.h"

#include "../../core/IEcamera.h"

IE_BEGIN

IETotalScene::IETotalScene()
{
	m_triggerManager = NULL;
}

IETotalScene::~IETotalScene()
{
	__IE_RELEASE_DIF__(m_physicWorld);
}

void IETotalScene::Initialization(char * sceneName)
{
	IEScene::Initialization();

	//m_triggerManager = IETriggerManager::Create();
	m_physicWorld = IEPhysicWorld::Create();
	m_creaturesLayer = IELayer::Create();
	m_propLayer = IELayer::Create();
	m_drawScene = IEDrawScene::Create();
	m_map = IEMap::Create(sceneName);

	IENode::AddChild(m_map);
	IENode::AddChild(m_creaturesLayer);
	IENode::AddChild(m_propLayer);
	IENode::AddChild(m_drawScene);
}

IETotalScene * IETotalScene::CreateAndRetain(char * sceneName)
{
	IETotalScene * scene = new IETotalScene();
	scene->Initialization(sceneName);
	scene->Retain();
	return scene;
}

void IETotalScene::Run()
{
	Visit();

	m_physicWorld->Run();
	//m_triggerManager->Run();
	m_drawScene->Run();

	//带所有的元素渲染完毕 这个时候 根据IEPlayer的方位定位camera最精准
	//const float * translate = m_player->GetTranslate();
	//IECamera::Share()->SetCameraPosi(translate[0], translate[1]);
	//IECamera::Share()->Run();
}

void IETotalScene::AddChild(IECreature * creature)
{
	m_creaturesLayer->AddChild(creature);
}

void IETotalScene::AddChild(IEPlayer * player)
{
	m_player = player;

	m_creaturesLayer->AddChild(player);
}

IETriggerManager * IETotalScene::GetTriggerManager()
{
	return m_triggerManager;
}

IEPhysicWorld * IETotalScene::GetPhysicWorld()
{
	return m_physicWorld;
}

IELayer * IETotalScene::GetPropLayer()
{
	return m_propLayer;
}

IEContainer * IETotalScene::GetCreatures()
{
	return m_creaturesLayer->GetChilds();
}

IEPlayer * IETotalScene::GetPlayer()
{
	return m_player;
}

IEMap * IETotalScene::GetBindedMap()
{
	return m_map;
}

IE_END