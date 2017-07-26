/***********************************
* name     : IEdrawScene.h
* creater  : cosc
* info     : only scene 通过zIndex来决定渲染顺序
* date     : 2017/3/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DRAW_SCENE__
#define __IE_DRAW_SCENE__

#include "../../core/IElayer.h"

IE_BEGIN

class __IE_DLL__ IEDrawScene :public IELayer
{
public:
	IEDrawScene();
	virtual ~IEDrawScene();
	virtual void Initialization();
	static IEDrawScene * Create();
	static IEDrawScene * CreateAndRetain();

public:
	void AddDrawNode(IENode * node);

public:
	virtual void Run();
	virtual void Visit();
};

IE_END

#endif