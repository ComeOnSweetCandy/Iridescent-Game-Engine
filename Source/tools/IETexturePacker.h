/***********************************
* name     : IETexturePacker.h
* creater  : cosc
* info     : 2d texture packer tool
* date     : 2017/6/30
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TEXTURE_PACKER__
#define __IE_TEXTURE_PACKER__

#include "IEtexture.h"

IE_BEGIN

class IETexturePackerElement:public IEObject
{
public:
	IETexture * _Texture;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _Size;

	//最终放置下来的位置信息
	unsigned int _X;
	unsigned int _Y;
};

class IEContainer;

class __IE_DLL__ IETexturePacker :public IEObject
{
public:
	IETexturePacker();
	virtual ~IETexturePacker();
	virtual void Initialization(const char * textureName);
	static IETexturePacker * Create(const char * textureName);

public:
	void AddTexture(IETexture * texture);
	IEContainer * Run();

private:
	void AutoEnlarge();
	void SortTexture(unsigned int index);

public:
	IEString m_textureName;
	IEContainer * m_textureContainer;
	IEContainer * m_pointsContainer;

	unsigned int m_width;
	unsigned int m_height;
};

IE_END

#endif