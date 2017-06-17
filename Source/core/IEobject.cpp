#define __IE_DLL_EXPORTS__
#include "IEobject.h"
#include "container/IEautoReleasePool.h"

IE_BEGIN

IEObject::IEObject()
{
	m_referenceCount = 0;
}

IEObject::~IEObject()
{

}

void IEObject::Release()
{
	m_referenceCount--;
	if (m_referenceCount < 0)
	{
		__IE_WARNING__("reference count less than 0.\n");
	}
	if (m_referenceCount == 0)
	{
		delete this;
	}
}

void IEObject::ReleaseDisreference()
{
	if (m_referenceCount < 0)
	{
		__IE_WARNING__("reference count less than 0\n");
	}
	if (m_referenceCount == 0)
	{
		delete this;
	}
}

void IEObject::Retain()
{
	m_referenceCount++;
}

void IEObject::Discard()
{
	m_referenceCount--;
}

bool IEObject::IsRefered()
{
	return m_referenceCount ? true : false;
}

int IEObject::GetReferencesCount()
{
	return m_referenceCount;
}

void IEObject::Initialization()
{

}

IEObject * IEObject::Create()
{
	IEObject * object = new IEObject();
	object->Initialization();
	return object;
}

void IEObject::AutoRelease()
{
	IEAutoReleasePool::Share()->PushToAutoReleasePool(this);
}

void IEObject::DiscardAndAutoRelease()
{
	this->Discard();
	IEAutoReleasePool::Share()->PushToAutoReleasePool(this);
}

IE_END