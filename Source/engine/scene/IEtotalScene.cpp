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
	m_physicWorld->Run();			//�ȼ�����һ֡������������

	DrawScene();					//���Ƴ����е���������
}

void IETotalScene::DrawScene()
{
	FollowCamera();					//������ֵ �趨�������λ��
	m_physicWorld->Draw();			//��������Ԫ��
	this->Visit();					//�������е�����
}

void IETotalScene::FollowCamera()
{
	//�����е�Ԫ����Ⱦ��� ���ʱ�� ����IEPlayer�ķ�λ��λcamera�׼
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