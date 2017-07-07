/***********************************
* name     : IETexture.h
* creater  : cosc
* info     : 2d texture
* date     : 2016/11/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TEXTURE__
#define __IE_TEXTURE__

#include "../core/IEobject.h"
#include "../type/IEgrid.h"
#include "IEimage.h"

IE_BEGIN

class __IE_DLL__ IETexture:public IEObject
{
public:
	IETexture();
	virtual ~IETexture();
	virtual void Initialization(const char * textureName);
	static IETexture * Create(const char * textureName);

public:
	GLuint * GetTexturesId();

	//预加载贴图
	void PreloadTexture(const char * textureName);

private:
	void LoadTexture();
	void LoadTextureInfo();

public:
	unsigned char m_textureFramesCount;
	GLuint * m_textureId;
	IEGrid * m_textureSize;
	IEString m_textureName;

	float * m_timeAxis;								//每帧时间点
	int m_triggerAxis;								//关键帧

	friend class IESprite;
};

IE_END

#endif