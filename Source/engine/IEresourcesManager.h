/***********************************
* name     : IEresourceManager.h
* creater  : cosc
* info     : 统一的资源管理器
* date     : 2017/4/2
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_RESOURCE_NODE__
#define __IE_RESOURCE_NODE__

#include "../core/IEobject.h"

IE_BEGIN

class IEResourcesManager:public IEObject
{
public:
	IEResourcesManager();
	virtual ~IEResourcesManager();
	virtual void Initialization();
	static IEResourcesManager * CreateAndRetain();

public:
	virtual void Run();
};

IE_END

#endif