/***********************************
* name     : IETriggerWarn.h
* creater  : cosc
* info     : 普通的包围式检测 在范围内就触发
* date     : 2017/9/5
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TRIGGER_WARN__
#define __IE_TRIGGER_WARN__

#include "IETrigger.h"

IE_BEGIN

class __IE_DLL__ IETriggerWarn :public IETrigger
{
public:
	IETriggerWarn();
	virtual ~IETriggerWarn();
	virtual void Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);
	static IETriggerWarn * Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne);

public:
	virtual void Collision(IEPhysicNode * physicNode);
};

IE_END

#endif