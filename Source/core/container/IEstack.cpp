#define __IE_DLL_EXPORTS__
#include "IEstack.h"

IE_BEGIN

IEStack::IEStack()
{
	m_head = new IEStackElement();
	m_head->m_object = NULL;
	m_head->m_nextElement = NULL;
	m_end = NULL;
	m_count = 0;
}

IEStack::~IEStack()
{
	if (m_head)
	{
		EmptyContainer();
		delete m_head;
	}
}

void IEStack::Initialization()
{

}

IEStack * IEStack::Create()
{
	IEStack * object = new IEStack();
	object->Initialization();
	return object;
}

IEStack * IEStack::CreateAndRetain()
{
	IEStack * object = new IEStack();
	object->Initialization();
	object->Retain();
	return object;
}

void IEStack::PushFromBegining(IEObject * object)
{
	IEStackElement * newElement = new IEStackElement();
	newElement->m_object = object;
	if (m_head->m_nextElement == NULL)
	{
		m_end = newElement;
	}
	newElement->m_nextElement = m_head->m_nextElement;
	m_head->m_nextElement = newElement;
	object->Retain();
	m_count++;
}

void IEStack::PushFromEnding(IEObject * object)
{
	IEStackElement * newElement = new IEStackElement();
	newElement->m_object = object;
	newElement->m_nextElement = NULL;
	if (m_head->m_nextElement == NULL)
	{
		m_end = m_head;
	}
	m_end->m_nextElement = newElement;
	m_end = newElement;
	object->Retain();
	m_count++;
}

IEObject * IEStack::PopFromBegining()
{
	if (m_head->m_nextElement != NULL)
	{
		IEStackElement * deleteElement = m_head->m_nextElement;
		m_head->m_nextElement = deleteElement->m_nextElement;
		if (m_head->m_nextElement == NULL)
		{
			m_end = NULL;
		}
		
		IEObject * obj = deleteElement->m_object;
		deleteElement->m_nextElement = NULL;
		delete deleteElement;
		m_count--;

		obj->Discard();
		return obj;
	}
	return NULL;
}

IEObject * IEStack::PopFromEnding()
{
	if (m_end != NULL)
	{
		IEStackElement * curElement = m_head;
		unsigned int index = 0;
		while (index != (m_count - 1))
		{
			curElement = curElement->m_nextElement;
			index++;
		}

		IEStackElement * deleteElement = m_end;
		if (curElement == m_head)
		{
			m_head->m_nextElement = NULL;
			m_end = NULL;
		}
		else
		{
			m_end = curElement;
			m_end->m_nextElement = NULL;
		}

		IEObject * obj = deleteElement->m_object;
		deleteElement->m_nextElement = NULL;
		delete deleteElement;
		m_count--;

		obj->DiscardAndAutoRelease();
		return obj;
	}
	return NULL;
}

IEObject * IEStack::GetFromEnding()
{
	if (m_end && m_end->m_object)
	{
		return m_end->m_object;
	}
	return NULL;
}

void IEStack::EmptyContainer()
{
	IEStackElement * curElement = m_head->m_nextElement;
	while (curElement)
	{
		IEStackElement * deleteElement = curElement;
		curElement = curElement->m_nextElement;

		deleteElement->m_object->Release();
		deleteElement->m_nextElement = NULL;
		delete deleteElement;
	}

	m_count = 0;
	m_end = NULL;
	m_head->m_nextElement = NULL;
}

unsigned int IEStack::Count()
{
	return m_count;
}

bool IEStack::IsEmpty()
{
	return m_count ? true : false;
}

IE_END