#define __IE_DLL_EXPORTS__
#include "IEtotalScene.h"

IE_BEGIN

IETotalScene::IETotalScene()
{
	m_triggerManager = NULL;
}

IETotalScene::~IETotalScene()
{
	__IE_RELEASE_DIF__(m_triggerManager);
	__IE_RELEASE_DIF__(m_physicWorld);
}

void IETotalScene::Initialization(char * sceneName)
{
	IEScene::Initialization();

	m_triggerManager = IETriggerManager::Create();
	m_physicWorld = IEPhysicWorld::Create();
	m_creaturesLayer = IELayer::Create();
	m_propLayer = IELayer::Create();
	m_map = IEMap::Create(sceneName);

	IENode::AddChild(m_map);
	IENode::AddChild(m_creaturesLayer);
	IENode::AddChild(m_propLayer);
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
	m_triggerManager->Run();
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