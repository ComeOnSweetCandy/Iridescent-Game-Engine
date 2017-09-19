#define __IE_DLL_EXPORTS__
#include "IEtotalScene.h"

#include "../../core/IEcamera.h"

IE_BEGIN

IETotalScene::IETotalScene()
{

}

IETotalScene::~IETotalScene()
{
	__IE_RELEASE_DIF__(m_physicWorld);
}

void IETotalScene::Initialization(char * sceneName)
{
	IEScene::Initialization();

	m_map = IEMap::Create(sceneName);
	m_creaturesLayer = IELayer::Create();
	m_propLayer = IELayer::Create();
	m_physicWorld = IEPhysicWorld::Create();

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
	m_physicWorld->Run();			//先计算上一帧的所有物理结果

	DrawScene();					//绘制场景中的所有内容
}

void IETotalScene::DrawScene()
{
	FollowCamera();					//根据数值 设定摄像机的位置
	m_physicWorld->Draw();			//绘制物理元素
	this->Visit();					//访问所有的子类
}

void IETotalScene::FollowCamera()
{
	//带所有的元素渲染完毕 这个时候 根据IEPlayer的方位定位camera最精准
	const float * translate = m_player->GetTranslate();
	IECamera::Share()->SetCameraPosi(translate[0], translate[1]);
	IECamera::Share()->Run();
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