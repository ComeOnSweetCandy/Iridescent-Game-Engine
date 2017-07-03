#define __IE_DLL_EXPORTS__
#include "IEcontianer.h"
#include "../IEnode.h"

IE_BEGIN

IEContainer::IEContainer()
{
	m_objectsCount = 0;
	m_maxCapacity = 0;
	m_sortingOffset = -1;
	m_objectsContainer = NULL;
	m_isChanged = false;
}

IEContainer::~IEContainer()
{
	if (m_maxCapacity)
	{
		EmptyContainer();
	}
}

void IEContainer::Initialization(int maxCapacity)
{
	InitMaxCapacity(maxCapacity);
}

IEContainer * IEContainer::Create(int maxCapacity)
{
	IEContainer * object = new IEContainer();
	object->Initialization(maxCapacity);
	return object;
}

IEContainer * IEContainer::CreateAndRetain(int maxCapacity)
{
	IEContainer * object = new IEContainer();
	object->Initialization(maxCapacity);
	object->Retain();
	return object;
}

void IEContainer::InitMaxCapacity(int maxCapacity)
{
	if (maxCapacity)
	{
		m_maxCapacity = maxCapacity;
		m_objectsContainer = (IEObject **)malloc(m_maxCapacity * sizeof(int));
	}
}

const int& IEContainer::Count()
{
	return m_objectsCount;
}

const int& IEContainer::AddCount(int value)
{
	m_objectsCount += value;
	return m_objectsCount;
}

const int& IEContainer::Max()
{
	return m_maxCapacity;
}

IEObject ** IEContainer::GetContainer()
{
	return m_objectsContainer;
}

void IEContainer::Push(IEObject * object)
{
	if (object != NULL)
	{
		if (m_maxCapacity == 0)
		{
			m_maxCapacity = 1;
			m_objectsContainer = (IEObject **)malloc(m_maxCapacity * sizeof(int));
			m_objectsContainer[0] = object;
		}
		else
		{
			if (m_objectsCount >= m_maxCapacity)
			{
				m_maxCapacity = m_maxCapacity * 2;
				m_objectsContainer = (IEObject **)realloc(m_objectsContainer, m_maxCapacity * sizeof(int));

				//将新开拓空间进行清理
				for (int index = m_objectsCount; index < m_maxCapacity; index++)
				{
					m_objectsContainer[index] = NULL;
				}
			}
			m_objectsContainer[m_objectsCount] = object;
		}
		m_objectsCount++;
		m_isChanged = true;
		object->Retain();
	}
	else
	{
		__IE_WARNING__("insert into container a null ptr is error.\n");
	}
}

void IEContainer::PushArrays(IEObject ** objects, int count)
{
	for (int index = 0; index < count; index++)
	{
		Push(objects[index]);
	}
}

IEObject * IEContainer::Pop(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				IEObject * object = m_objectsContainer[index];

				m_objectsContainer[index]->DiscardAndAutoRelease();
				m_objectsContainer[index] = NULL;
				m_objectsCount--;
				m_isChanged = true;
				return object;
			}
		}
	}
	return NULL;
}

IEObject * IEContainer::Pop(int index)
{
	if (index >= m_objectsCount)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	IEObject * object = m_objectsContainer[index];

	m_objectsContainer[index]->DiscardAndAutoRelease();
	m_objectsContainer[index] = NULL;
	m_objectsCount--;
	m_isChanged = true;
	return object;
}

IEObject * IEContainer::PopTop()
{
	if (m_objectsCount > 0)
	{
		int index = m_objectsCount - 1;
		IEObject * object = m_objectsContainer[index];

		m_objectsContainer[index]->DiscardAndAutoRelease();
		m_objectsContainer[index] = NULL;
		m_objectsCount--;
		m_isChanged = true;
		return object;
	}
	return NULL;
}

IEObject * IEContainer::Delete(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				IEObject * object = m_objectsContainer[index];

				m_objectsContainer[index]->Release();
				m_objectsContainer[index] = NULL;
				m_objectsCount--;
				m_isChanged = true;
				return object;
			}
		}
	}
	return NULL;
}

IEObject * IEContainer::Delete(int index)
{
	if (index >= m_objectsCount)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	IEObject * object = m_objectsContainer[index];

	m_objectsContainer[index]->Release();
	m_objectsContainer[index] = NULL;
	m_objectsCount--;
	m_isChanged = true;
	return object;
}

IEObject * IEContainer::PopWithClean(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				IEObject * object = m_objectsContainer[index];

				m_objectsContainer[index]->DiscardAndAutoRelease();
				m_objectsContainer[index] = m_objectsContainer[m_objectsCount - 1];
				m_objectsContainer[m_objectsCount - 1] = NULL;
				m_objectsCount--;
				m_isChanged = true;
				return object;
			}
		}
	}

	ReduceSpace();
	return NULL;
}

IEObject * IEContainer::PopWithClean(int index)
{
	if (index >= m_objectsCount)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	IEObject * object = m_objectsContainer[index];

	m_objectsContainer[index]->DiscardAndAutoRelease();
	m_objectsContainer[index] = m_objectsContainer[m_objectsCount - 1];
	m_objectsContainer[m_objectsCount - 1] = NULL;
	m_objectsCount--;
	m_isChanged = true;

	ReduceSpace();
	return object;
}


IEObject * IEContainer::DeleteWithClean(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				IEObject * object = m_objectsContainer[index];

				m_objectsContainer[index]->Release();
				m_objectsContainer[index] = m_objectsContainer[m_objectsCount - 1];
				m_objectsContainer[m_objectsCount - 1] = NULL;
				m_objectsCount--;
				m_isChanged = true;
				return object;
			}
		}
	}

	ReduceSpace();
	return NULL;
}

IEObject * IEContainer::DeleteWithClean(int index)
{
	if (index >= m_objectsCount)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	IEObject * object = m_objectsContainer[index];

	m_objectsContainer[index]->Release();
	m_objectsContainer[index] = m_objectsContainer[m_objectsCount - 1];
	m_objectsContainer[m_objectsCount - 1] = NULL;
	m_objectsCount--;
	m_isChanged = true;

	ReduceSpace();
	return object;
}

IEObject * IEContainer::Find(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				return object;
			}
		}
	}
	return NULL;
}

IEObject * IEContainer::Find(int index)
{
	if (index < 0)
	{
		return NULL;
	}
	if (index < m_objectsCount)
	{
		return m_objectsContainer[index];
	}
	return NULL;
}

IEObject * IEContainer::operator[](int index)
{
	if (index < 0)
	{
		return NULL;
	}
	if (index < m_objectsCount)
	{
		return m_objectsContainer[index];
	}
	return NULL;
}

int IEContainer::Index(IEObject * object)
{
	if (object != NULL)
	{
		for (int index = 0; index < m_objectsCount; index++)
		{
			if (m_objectsContainer[index] == object)
			{
				return index;
			}
		}
	}
	return -1;
}

void IEContainer::CleanSpace()
{
	if (!m_isChanged)
	{
		return;
	}

	for (int index = 0, nextObjectIndex = 1; index < m_maxCapacity; index++)
	{
		if (m_objectsContainer[index] == NULL)
		{
			if (nextObjectIndex <= index)
			{
				nextObjectIndex = index + 1;
			}

			while (nextObjectIndex < m_maxCapacity)
			{
				if (m_objectsContainer[nextObjectIndex] != NULL)
				{
					m_objectsContainer[index] = m_objectsContainer[nextObjectIndex];
					m_objectsContainer[nextObjectIndex] = NULL;

					break;
				}
				nextObjectIndex++;
			}
		}
	}
	ReduceSpace();
}

void IEContainer::ReduceSpace()
{
	if (!m_isChanged)
	{
		return;
	}
	m_isChanged = false;

	if (m_objectsCount == 0)
	{
		m_maxCapacity = 0;
		free(m_objectsContainer);
		m_objectsContainer = NULL;
		return;
	}

	bool shouldRealloc = false;
	while (m_objectsCount <= (m_maxCapacity / 2))
	{
		m_maxCapacity = m_maxCapacity / 2;
		shouldRealloc = true;
	}
	if (shouldRealloc)
	{
		if (m_maxCapacity == 0)
		{
			free(m_objectsContainer);
			m_objectsContainer = NULL;
		}
		else
		{
			m_objectsContainer = (IEObject **)realloc(m_objectsContainer, sizeof(int)*m_maxCapacity);
		}
	}
}

void IEContainer::ReverseSpace()
{
	for (int index = 0; index < m_objectsCount / 2; index++)
	{
		IEObject * object = m_objectsContainer[index];
		m_objectsContainer[index] = m_objectsContainer[m_objectsCount - 1 - index];
		m_objectsContainer[m_objectsCount - 1 - index] = object;
	}
}

void IEContainer::Merge(IENode ** sourceArr, IENode ** tempArr, int startIndex, int midIndex, int endIndex)
{
	int i = startIndex, j = midIndex + 1, k = startIndex;
	while (i != midIndex + 1 && j != endIndex + 1)
	{
		if (m_sortingOffset > 0)
		{
			int left = *(int *)((char *)(sourceArr[i]) + m_sortingOffset);
			int right = *(int *)((char *)(sourceArr[j]) + m_sortingOffset);

			if (left < right)
			{
				tempArr[k++] = sourceArr[j++];
			}
			else
			{
				tempArr[k++] = sourceArr[i++];
			}
		}
		else
		{
			if (sourceArr[i]->GetZIndex() < sourceArr[j]->GetZIndex())
			{
				tempArr[k++] = sourceArr[j++];
			}
			else
			{
				tempArr[k++] = sourceArr[i++];
			}
		}
	}
	while (i != midIndex + 1)
	{
		tempArr[k++] = sourceArr[i++];
	}
	while (j != endIndex + 1)
	{
		tempArr[k++] = sourceArr[j++];
	}
	for (i = startIndex; i <= endIndex; i++)
	{
		sourceArr[i] = tempArr[i];
	}
}

void IEContainer::MergeSort(IENode ** sourceArr, IENode ** tempArr, int startIndex, int endIndex)
{
	int midIndex;
	if (startIndex < endIndex)
	{
		midIndex = (startIndex + endIndex) / 2;
		MergeSort(sourceArr, tempArr, startIndex, midIndex);
		MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);
		Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
	}
}

void IEContainer::Sorting(int offset)
{
	if (m_isChanged && m_objectsCount > 0)
	{
		m_sortingOffset = offset;

		IENode ** tempObjectsContainer = new IENode *[m_objectsCount];
		MergeSort((IENode **)m_objectsContainer, (IENode **)tempObjectsContainer, 0, m_objectsCount-1);
		delete[] tempObjectsContainer;

		m_isChanged = false;
	}
}

void IEContainer::EmptyContainer()
{
	if (m_maxCapacity)
	{
		for (int index = 0; index < m_maxCapacity; index++)
		{
			if (m_objectsContainer[index])
			{
				m_objectsContainer[index]->Release();
				m_objectsContainer[index] = NULL;
			}
		}
		m_objectsCount = 0;
		m_maxCapacity = 0;
		free(m_objectsContainer);
		m_objectsContainer = NULL;
	}
}

void IEContainer::ReleaseDisreferences()
{
	int index = 0;
	int objectsCount = m_objectsCount;
	while (index < m_objectsCount)
	{
		IEObject * o = m_objectsContainer[index];
		m_objectsContainer[index]->Discard();
		if (m_objectsContainer[index]->IsRefered() == false)
		{
			m_objectsContainer[index]->ReleaseDisreference();
		}
		else
		{

		}
		m_objectsContainer[index] = NULL;
		index++;
	}

	//无论如何都会被释放干净
	m_objectsCount = 0;
	m_isChanged = true;
	ReduceSpace();
}

IE_END