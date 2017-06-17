/***********************************
* name     : IEautoReleasePool.h
* creater  : cosc
* info     : auto release pool
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_AUTORELEASEPOOL__
#define __IE_AUTORELEASEPOOL__

#include "../../global/IEstdafx.h"
#include "IEcontianer.h"

IE_BEGIN

class IEObject;

class __IE_DLL__ IEAutoReleasePool :public IEObject
{
public:
	IEAutoReleasePool();
	virtual ~IEAutoReleasePool();
	virtual void Initialization();
	static IEAutoReleasePool * Share();

public:
	void PushToAutoReleasePool(IEObject * autoReleaseObject);
	void ReleasePool();
	void Run();

private:
	static IEAutoReleasePool * m_StaticAutoReleasePool;
	IEContainer * m_poolContainer;
};

IE_END

#endif