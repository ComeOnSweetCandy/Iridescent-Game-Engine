#define __IE_DLL_EXPORTS__
#include "IEautoReleasePool.h"
#include "../IEobject.h"

IE_BEGIN

IEAutoReleasePool * IEAutoReleasePool::m_StaticAutoReleasePool = NULL;

IEAutoReleasePool::IEAutoReleasePool()
{
	m_poolContainer = IEContainer::CreateAndRetain();
}

IEAutoReleasePool::~IEAutoReleasePool()
{
	m_poolContainer->ReleaseDisreferences();
	m_poolContainer->Release();
}

void IEAutoReleasePool::Initialization()
{
	Retain();
}

IEAutoReleasePool * IEAutoReleasePool::Share()
{
	if (m_StaticAutoReleasePool == NULL)
	{
		m_StaticAutoReleasePool = new IEAutoReleasePool();
		m_StaticAutoReleasePool->Initialization();
	}
	return m_StaticAutoReleasePool;
}

void IEAutoReleasePool::PushToAutoReleasePool(IEObject * autoReleaseObject)
{
	m_poolContainer->Push(autoReleaseObject);
}

void IEAutoReleasePool::ReleasePool()
{
	m_poolContainer->EmptyContainer();
}

void IEAutoReleasePool::Run()
{
	m_poolContainer->ReleaseDisreferences();
}

IE_END
