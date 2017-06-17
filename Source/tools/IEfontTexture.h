/***********************************
* name     : IEfontTexture.h
* creater  : cosc
* info     : 2d texture
* date     : 2017/3/9
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FONT_TEXTURE__
#define __IE_FONT_TEXTURE__

#include "../core/IEobject.h"
#include "../type/IEgrid.h"
#include "IEimage.h"
#include "../core/container/IEdictionary.h"

IE_BEGIN

class __IE_DLL__ IEFontTexture:public IEObject
{
public:
	IEFontTexture();
	virtual ~IEFontTexture();
	virtual void Initialization(const IEString &textureName);
	static IEFontTexture * Create(const char * textureName);
	static IEFontTexture * Share();

public:
	void PreloadFontTexture(const char * textureName);

private:
	void LoadFontTexture();

private:
	static IEFontTexture * m_fontTexture;

	GLuint * m_textureId;
	IEGrid m_textureSize;
	IEString m_textureName;

	friend class IEText;
};

IE_END

#endif