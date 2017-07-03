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
	IEImage * _Image;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _Size;

	//最终放置下来的位置信息
	unsigned int _X;
	unsigned int _Y;

	//存在于的动作组
	unsigned char _Group;

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
	void AddImage(IEImage * image);
	void AddTexture(IETexture * texture);
	IEContainer * Run();
	void Save();							//生成新的贴图并且存储于本地 同时生成plist文件

private:
	void AutoEnlarge();
	void SortTexture(unsigned int index);
	void SortPoints();						//对于点进行特殊的排序 首先将Y轴越低的放前面 Y轴相同 X轴越低的放前面

public:
	IEString m_textureName;
	IEContainer * m_textureContainer;
	IEContainer * m_pointsContainer;

	unsigned int m_width;
	unsigned int m_height;
};

IE_END

#endif