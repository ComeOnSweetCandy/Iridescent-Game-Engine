#define __IE_DLL_EXPORTS__
#include "IEslot.h"

IE_BEGIN

IESlot::IESlot()
{

}

IESlot::~IESlot()
{

}

void IESlot::Initialization()
{
	IEWidget::Initialization();
}

IESlot * IESlot::Create()
{
	IESlot * ui = new IESlot();
	ui->Initialization();
	return ui;
}

void IESlot::SetButton(int buttonIndex, IEProp * usedProp, char * textureName, bool isWorking)
{
	IEWidget ** buttons = (IEWidget **)w_childs->GetContainer();
	int buttonCount = w_childs->Count();

	if (buttonIndex >= buttonCount)
	{
		return;
	}
	else
	{
		//buttons[buttonIndex]->SetWidgetWorking(isWorking);
		//buttons[buttonIndex]->BindWidgetCallback(IEWidgetCallback(&IEProp::PressCallback), usedProp);
		//buttons[buttonIndex]->ChangeTexture(textureName);
	}
}

IE_END