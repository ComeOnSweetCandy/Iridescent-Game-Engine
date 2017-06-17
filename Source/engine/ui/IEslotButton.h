/***********************************
* name     : IEslotButton.h
* creater  : cosc
* info     : ui widget short cut button
* date     : 2017/4/2
* version  : 1.0
* remark   : nothing
************************************/

#ifndef __IE_SLOT_BUTTON__
#define __IE_SLOT_BUTTON__

#include "../../ui/IEwidget.h"

IE_BEGIN

class __IE_DLL__ IESlotButton :public IEWidget
{
public:
	IESlotButton();
	virtual ~IESlotButton();
	virtual void Initialization();
	static IESlotButton * Create();

protected:
	virtual void WidgetCallback();
};

IE_END

#endif