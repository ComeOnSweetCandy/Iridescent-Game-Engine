/***********************************
* name     : IElayer.h
* creater  : cosc
* info     : ui layer
* date     : 2016/11/24
* version  : 1.0
* remark   : content ui element
************************************/

#ifndef __IE_LAYER__
#define __IE_LAYER__

#include "IEnode.h"
#include "element/IEElement.h"

IE_BEGIN

class __IE_DLL__ IELayer :public IENode
{
public:
	IELayer();
	virtual ~IELayer();
	virtual void Initialization();
	static IELayer * Create();

public:
	virtual void DrawNode();

	void DrawBackground();
	void DrawBorder();

private:
	bool m_display;
};

IE_END

#endif