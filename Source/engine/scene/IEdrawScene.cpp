#define __IE_DLL_EXPORTS__
#include "IEdrawScene.h"

IE_BEGIN

IEDrawScene::IEDrawScene()
{

}

IEDrawScene::~IEDrawScene()
{

}

void IEDrawScene::Initialization()
{
	IELayer::Initialization();
}

IEDrawScene * IEDrawScene::Create()
{
	IEDrawScene * layer = new IEDrawScene();
	layer->Initialization();
	return layer;
}

IEDrawScene * IEDrawScene::CreateAndRetain()
{
	IEDrawScene * layer = new IEDrawScene();
	layer->Initialization();
	layer->Retain();
	return layer;
}

void IEDrawScene::AddDrawNode(IENode * node)
{
	m_childs->Push(node);
}

void IEDrawScene::Run()
{
	m_childs->Sorting();
	IENode ** nodes = (IENode **)(m_childs->GetContainer());
	for (int index = 0; index < m_childs->Count(); index++)
	{
		nodes[index]->LoadSavedModelMatrix();
		nodes[index]->DrawNode();
	}

	m_childs->EmptyContainer();
}

void IEDrawScene::Visit()
{

}

IE_END