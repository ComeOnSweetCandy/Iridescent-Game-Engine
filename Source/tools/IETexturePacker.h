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

typedef struct __iePackedGroup
{
	char * _GroupName;
	unsigned short _GroupIndex;
	unsigned short _SameIndex;
	unsigned short _FrapsCount;
	unsigned short _SameCount;
	
	__iePackedGroup * _Same;
	__iePackedGroup * _Next;
}IEPackedGroup;

class IEPackedImage:public IEObject
{
public:
	IEPackedImage(){};
	~IEPackedImage(){ _Image->ReleaseDisreference(); }

public:
	IEImage * _Image;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _Size;

	//最终放置下来的位置信息
	unsigned int _X;
	unsigned int _Y;

	//存在于的动作组
	unsigned short _GroupIndex;
	unsigned short _SameIndex;
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
	void AddImage(IEImage * image, const char * groupName, float endTime = 0.0f, unsigned char sameIndex = 0);		//放入image的数据时，也填充group
	void SaveTexture();											//生成新的贴图并且存储于本地 同时生成plist文件

private:
	IEContainer * Recombine();									//生成贴图组的存放的各种数据信息
	void AutoEnlarge();
	void SortTexture(unsigned int index);
	void SortPoints();											//对于点进行特殊的排序 首先将Y轴越低的放前面 Y轴相同 X轴越低的放前面

public:
	IEString m_textureName;
	IEContainer * m_textureContainer;
	IEContainer * m_pointsContainer;
	IEPackedGroup * m_textureGroupHead;
	unsigned short m_groupMaxIndex;

	unsigned int m_width;
	unsigned int m_height;
};

IE_END

#endif