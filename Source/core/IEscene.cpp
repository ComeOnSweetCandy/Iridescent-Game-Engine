#define __IE_DLL_EXPORTS__
#include "IEscene.h"

IE_BEGIN

IEScene::IEScene()
{

}

IEScene::~IEScene()
{
	m_parent = NULL;
}

void IEScene::Initialization()
{
	IENode::Initialization();
}

IEScene * IEScene::Create()
{
	IEScene * object = new IEScene();
	object->Initialization();
	return object;
}

void IEScene::AddChild(IELayer * node)
{
	IENode::AddChild(node);
}

void IEScene::RemoveChild(IELayer * node)
{
	IENode::RemoveChild(node);
}

void IEScene::Run()
{
	Visit();
}

IE_END
