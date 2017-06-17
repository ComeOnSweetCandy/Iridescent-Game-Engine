/***********************************
* name     : IEtext.h
* creater  : cosc
* info     : text
* date     : 2017/3/6
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TEXT__
#define __IE_TEXT__

#include "IEsprite.h"
#include "../../tools/IEfontTTF.h"

IE_BEGIN

#define IE_UNICODE_HEAD(__unicode__) ((0xff00&__unicode__)>>8)
#define IE_UNICODE_TAIL(__unicode__) (0x00ff&__unicode__)

enum IETextAlign
{
	__text_align_left__,
	__text_align_center__,
	__text_align_right__
};

class __IE_DLL__ IEText :public IESprite
{
public:
	IEText();
	virtual ~IEText();
	virtual void Initialization(const char * text);
	static IEText * Create(const char * text);

protected:
	virtual void DrawNode();

public:
	void setText(const char * text);
	void setAlign(IETextAlign textAlign);
	void GBKToUnicode();
	void ReckonTextareaSize();

private:
	int m_textCount;
	
	IEString m_defaultBackground;
	IEString m_text;
	IETextAlign m_textAlign;
	unsigned short * m_unicodeText;
};

IE_END

#endif