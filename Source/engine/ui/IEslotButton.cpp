#define __IE_DLL_EXPORTS__
#include "IEslotButton.h"
#include "../../control/IEkeyboard.h"

IE_BEGIN

IESlotButton::IESlotButton()
{

}

IESlotButton::~IESlotButton()
{

}

void IESlotButton::Initialization()
{
	IEWidget::Initialization();

	//IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IESlotButton::WidgetCallback), this, DIK_1 + index);
}

IESlotButton * IESlotButton::Create()
{
	IESlotButton * object = new IESlotButton();
	object->Initialization();
	return object;
}

void IESlotButton::WidgetCallback()
{
	//IEWidget::WidgetCallback();
}

IE_END