/***********************************
* name     : IEcontainer.h
* creater  : cosc
* info     : objects container
* date     : 2016/11/21
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CONTAINER__
#define __IE_CONTAINER__

#include "../IEobject.h"

IE_BEGIN

class IENode;

class __IE_DLL__ IEContainer :public IEObject
{
public:
	IEContainer();
	virtual ~IEContainer(); 
	virtual void Initialization(int maxCapacity);
	static IEContainer * Create(int maxCapacity = 0);
	static IEContainer * CreateAndRetain(int maxCapacity = 0);

public:
	IEObject * operator[](int index);

	void Push(IEObject * object);
	void PushArrays(IEObject ** objects, int count);

	IEObject * Pop(IEObject * object);
	IEObject * Pop(int index);
	IEObject * PopTop();

	IEObject * PopWithClean(IEObject * object);
	IEObject * PopWithClean(int index);

	IEObject * Delete(IEObject * object);
	IEObject * Delete(int index);

	IEObject * DeleteWithClean(IEObject * object);
	IEObject * DeleteWithClean(int index);

	IEObject * Find(IEObject * object);
	IEObject * Find(int index);
	int Index(IEObject * object);

	void InitMaxCapacity(int maxCapacity);
	void CleanSpace();
	void ReduceSpace();
	void ReverseSpace();
	void EmptyContainer();
	const int& Count();
	const int& AddCount(int value);
	const int& Max();
	IEObject **GetContainer();

	/* IENode unique */
	void Sorting(int offset = -1);		//按内存中偏移位置的值来进行排序
	void Merge(IENode ** sourceArr, IENode ** tempArr, int startIndex, int midIndex, int endIndex);
	void MergeSort(IENode ** sourceArr, IENode ** tempArr, int startIndex, int endIndex);

private:
	void ReleaseDisreferences();

private:
	int m_objectsCount;
	int m_maxCapacity;
	bool m_isChanged;
	IEObject ** m_objectsContainer;

	int m_sortingOffset;	//进行特殊排序时所用

	friend class IEAutoReleasePool;
};

typedef IEContainer IEArray;

IE_END

#endif