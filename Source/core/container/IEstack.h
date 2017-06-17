/***********************************
* name     : IEobject.h
* creater  : cosc
* info     : class object
* c_date   : 2016/11/18
* l_date   : 2016/11/18
* version  : 1.0
* remark   : the base class that have been used
* in every class as base class.
************************************/

#ifndef __IE_STACK__
#define __IE_STACK__

#include "../IEobject.h"

IE_BEGIN

typedef struct IEStackElement
{
	IEObject * m_object;
	IEStackElement * m_nextElement;
}IEStackElement;

class __IE_DLL__ IEStack :public IEObject
{
public:
	IEStack();
	virtual ~IEStack();
	virtual void Initialization();
	static IEStack * Create();
	static IEStack * CreateAndRetain();

public:
	void PushFromBegining(IEObject * object);
	void PushFromEnding(IEObject * object);
	IEObject * PopFromBegining();
	IEObject * PopFromEnding();

	IEObject * GetFromEnding();

	void EmptyContainer();
	unsigned int Count();
	bool IsEmpty();

private:
	IEStackElement * m_head;
	IEStackElement * m_end;
	unsigned int m_count;
};

IE_END

#endif