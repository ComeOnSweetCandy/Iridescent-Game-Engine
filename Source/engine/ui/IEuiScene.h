/***********************************
* name     : IEuiScene.h
* creater  : cosc
* info     : ui scene
* date     : 2017/4/5
* version  : 1.0
* remark   : 
************************************/

#ifndef __IE_UI_SCENE__
#define __IE_UI_SCENE__

#include "../../ui/IEuiLayer.h"
#include "../../core/container/IEstack.h"

#include "../../engine/ui/IEslot.h"

IE_BEGIN

class __IE_DLL__ IEHtmlLabel :public IEObject
{
public:
	IEHtmlLabel()
	{
		h_widget = NULL;
		h_width = 0;
		h_height = 0;
		h_margin[0] = h_margin[1] = h_margin[2] = h_margin[3] = 0;
		h_offset_set[0] = h_offset_set[1] = h_offset_set[2] = h_offset_set[3] = false;
		h_color[0] = h_color[1] = h_color[2] = 0;
		h_relative = true;
	};
	~IEHtmlLabel()
	{

	};

public:
	IEWidget * h_widget;

	int h_width;
	int h_height;
	int h_margin[4];
	float h_offset[4];
	bool h_offset_set[4];
	int h_color[3];
	bool h_relative;
};

class __IE_DLL__ IEUiScene :public IEUiLayer
{
public:
	IEUiScene();
	virtual ~IEUiScene();
	virtual void Initialization();
	static IEUiScene * CreateAndRetain();

private:
	void LoadHTML();
	void AnalyzeHTML(char * html);
	void AnalyzeClassValue(IEString * classString);
	void AnalyzeStyleValue(IEString * styleString);

private:
	IEStack * m_htmlStack;
	IESlot * m_slot;
};

IE_END

#endif