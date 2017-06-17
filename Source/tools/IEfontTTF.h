/***********************************
* name     : IEfontttf.h
* creater  : cosc
* info     : ttf font display
* date     : 2016/12/1
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FONT_TTF__
#define __IE_FONT_TTF__

#include "../global/IEstdafx.h"
#include "../core/element/IEelement.h"
#include "IEfontTexture.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#pragma comment(lib,"libfreetype.lib")

IE_BEGIN

struct IECharacterInfo
{
	int s_offsetX;
	int s_offsetY;
	int s_occupyWidth;
};

class __IE_DLL__ IEFontTTF:public IEElement
{
public:
	IEFontTTF();
	~IEFontTTF();
	virtual void Initialization(const char * string, const char * fontName,unsigned int fontSize);
	static IEFontTTF * Create(const char * string, const char * fontName, unsigned int fontSize);
	static IEFontTTF * Share();

public:
	virtual void DrawNode();

	void DrawTTFText();
	void DrawWord(unsigned short int ch, int index);
	void SetDisplayString(char *str);
	void GBKToUnicode();
	int next_p2(int a);

public:
	void * GetWordInfo(unsigned short int ch, int &width, int &height, int &offsetX ,int &offsetY, int &occupyWidth, void * data);

	void WriteFontFile(unsigned short fontNumber, int everyFileNumber, char * filePosition, char *infoFilePosition);
	void ReadFontFile(char * filePosition, char *infoFilePosition);
	void WriteFontInfoFile();
	void ReadFontInfoFile();

private:
	static IEFontTTF * m_fontTTF;

	FT_Face m_fontFace;
	FT_Library m_library;

	IEString m_fontName;
	IEString m_displayString;
	wchar_t * m_displayStringUnicode;

public:
	IECharacterInfo * m_charactersInfo;
	int m_offsetTop;
	int m_offsetBottom;
	unsigned char m_fontSize;
};

IE_END

#endif