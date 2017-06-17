/***********************************
* name     : IEscene.h
* creater  : cosc
* info     : only scene
* date     : 2016/11/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SCENE__
#define __IE_SCENE__

#include "IElayer.h"

IE_BEGIN

class __IE_DLL__ IEScene :public IENode
{
public:
	IEScene();
	virtual ~IEScene();
	static IEScene * Create();
	virtual void Initialization();

public:
	virtual void Run();
	virtual void AddChild(IELayer * node);
	virtual void RemoveChild(IELayer * node);
};

IE_END

#endif