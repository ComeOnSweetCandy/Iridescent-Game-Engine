/***********************************
* name     : IEwidget.h
* creater  : cosc
* info     : ui widget base
* date     : 2017/4/1
* version  : 1.0
* remark   : base ui widget
************************************/

#ifndef __IE_WIEGET__
#define __IE_WIEGET__

#include "../core/element/IESprite.h"

IE_BEGIN

#define WIDGET_ALIGN_LEFT		0x1
#define WIDGET_ALIGN_CENTER		0x2
#define WIDGET_ALIGN_RIGHT		0x4
#define WIDGET_VERALIGN_TOP		0x8
#define WIDGET_VERALIGN_CENTER	0x10
#define WIDGET_VERALIGN_BOTTOM	0x20

class __IE_DLL__ IEWidget :public IESprite
{
public:
	IEWidget();
	virtual ~IEWidget();
	virtual void Initialization();
	static IEWidget * Create();

public:
	void SetWidgetColor(float r, float g, float b);
	void SetWidgetMargin(int left, int top, int right, int bottom);
	void SetWidgetOffset(float left, float top, float right, float bottom);
	void SetWidgetOffsetSet(bool left, bool top, bool right, bool bottom);
	void SetWidgetPosition(int x, int y);
	IEGrid GetWidgetPosition();
	void SetWidgetSize(int w, int h);
	IEGrid GetWidgetSize();
	void SetWarningLine(float warningLine);
	float GetWarningLine();
	void SetWidgetAlign(unsigned char alignType);
	void SetWidgetWorking(bool isWorking);
	void SetWidgetRelativeOrAbsolute(bool relative);
	bool GetWidgetRelativeOrAbsolute();

	virtual void BindWidgetCallback(IEWidgetCallback callback, IENode * node);
	virtual void WidgetCallback();

	IEArray * GetWidgetsArray();
	void AddWidgetChild(IEWidget * widget);
	void SetWidgetParent(IEWidget * widget);
	IEWidget * GetWidgetLeftBrother(int offset = 0);
	IEWidget * GetWidgetRightBrother(int offset = 0);
	int GetWidgetIndex();

protected:
	virtual void PreVisit();
	virtual void ChangeModelMatrix();
	virtual void RevertModelMatrix();
	virtual void Update();
	virtual void DrawNode();

	virtual void VisitChilds();

protected:
	IEWidgetCallback w_widgetCallback;
	IENode * w_node;
	IEWidget * w_parent;
	IEArray * w_childs;
	int w_warningLine;

	IEColor w_color;
	IEGrid w_position;
	IEGrid w_Size;
	int w_margin[4];
	float w_offset[4];
	bool w_offset_set[4];

	bool w_isRelative;
	bool w_isBlock;
	bool w_isWorking;
	unsigned char w_align;

	static IEGrid g_wPosition;
};

IE_END

#endif