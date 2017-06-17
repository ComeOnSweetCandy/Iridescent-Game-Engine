/***********************************
* name     : IEpickedProp.h
* creater  : cosc
* info     : damage prop
* date     : 2017/3/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PICKED_PROP__
#define __IE_PICKED_PROP__

#include "../IEprop.h"

IE_BEGIN

class __IE_DLL__ IEPickedProp :public IEProp
{
public:
	IEPickedProp();
	virtual ~IEPickedProp();
	virtual void Initialization(IETrigger * trigger, int propIndex, int propCount);
	static IEPickedProp * Create(IETrigger * trigger, int propIndex, int propCount);

public:
	virtual void InteractiveNode(IENode * strikeNode);
};

extern "C" __IE_DLL__ void CreatePickedProp(int propIndex, int propCount, float x, float y);

IE_END

#endif