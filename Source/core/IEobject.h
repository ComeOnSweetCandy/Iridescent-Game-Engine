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

#ifndef __IE_OBJECT__
#define __IE_OBJECT__

#include "../global/IEstdafx.h"
#include "container/IEautoRelease.h"

IE_BEGIN

class IEAutoReleasePool;

class __IE_DLL__ IEObject
{
public:
	IEObject();
	virtual ~IEObject();
	virtual void Initialization();
	static IEObject * Create();

public:
	void Retain();
	void Discard();
	void Release();
	void AutoRelease();
	void DiscardAndAutoRelease();
	void ReleaseDisreference();
	int GetReferencesCount();
	bool IsRefered();

private:
	int m_referenceCount;
};

typedef void (IEObject::*IECallback_void)();
typedef void (IEObject::*IECallbackWidget)(IEObject *);

IE_END

#endif