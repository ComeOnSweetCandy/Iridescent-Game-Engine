/***********************************
* name     : IEWarnTrigger.h
* creater  : cosc
* info     : 普通的包围式检测 在范围内就触发
* date     : 2017/9/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_WARN_TRIGGER__
#define __IE_WARN_TRIGGER__

#include "IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEWarnTrigger :public IETrigger
{
public:
	IEWarnTrigger();
	virtual ~IEWarnTrigger();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IEWarnTrigger * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif