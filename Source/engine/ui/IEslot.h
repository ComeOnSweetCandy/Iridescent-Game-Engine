/***********************************
* name     : IEslot.h
* creater  : cosc
* info     : ui short cut
* date     : 2017/4/1
* version  : 1.0
* remark   : base ui widget
************************************/

#ifndef __IE_SLOT__
#define __IE_SLOT__

#include "../../ui/IEwidget.h"
#include "../atom/prop/IEpropPack.h"

IE_BEGIN

class __IE_DLL__ IESlot :public IEWidget
{
public:
	IESlot();
	virtual ~IESlot();
	virtual void Initialization();
	static IESlot * Create();
	
public:
	void SetButton(int buttonIndex, IEUsedProp * usedProp, char * textureName, bool isWorking);
};

IE_END

#endif