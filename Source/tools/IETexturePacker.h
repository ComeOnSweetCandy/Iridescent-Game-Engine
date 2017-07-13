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

#include "IETexture.h"

IE_BEGIN

typedef struct __ieTextureGroup
{
	unsigned short _GroupIndex;
	char * _GroupName;
	unsigned short _FrapsCount;
	
	__ieTextureGroup * _Next;
}IETextureGroup;

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
	unsigned short _GroupIndex;
	unsigned short _FrapIndex;
	float _EndTime;
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
	void AddImage(IEImage * image, const char * groupName);		//放入image的数据时，也填充group
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
	IETextureGroup * m_textureGroupHead;

	unsigned int m_width;
	unsigned int m_height;
};

IE_END

#endif