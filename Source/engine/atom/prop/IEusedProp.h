/***********************************
* name     : IEusedProp.h
* creater  : cosc
* info     : used prop only exist in bag
* date     : 2017/3/30
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_USED_PROP__
#define __IE_USED_PROP__

#include "../IEprop.h"

IE_BEGIN

class IEPropPack;

class __IE_DLL__ IEUsedProp :public IEProp
{
public:
	IEUsedProp();
	virtual ~IEUsedProp();
	virtual void Initialization(int propIndex, int propCount);
	static IEUsedProp * Create(int propIndex, int propCount);

public:
	virtual void ClockTick();
	virtual void PressCallback(IENode * widget);

	virtual void UseProp();
	virtual void UsePropScript();
	void SetPropPack(IEPropPack * propPack);

private:
	IEPropPack * m_propPack;
};

IE_END

#endif