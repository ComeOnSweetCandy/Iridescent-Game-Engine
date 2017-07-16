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

	//���շ���������λ����Ϣ
	unsigned int _X;
	unsigned int _Y;

	//�����ڵĶ�����
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
	void AddImage(IEImage * image, const char * groupName, float endTime = 0.0f, unsigned char sameIndex = 0);		//����image������ʱ��Ҳ���group
	void SaveTexture();											//�����µ���ͼ���Ҵ洢�ڱ��� ͬʱ����plist�ļ�

private:
	IEContainer * Recombine();									//������ͼ��Ĵ�ŵĸ���������Ϣ
	void AutoEnlarge();
	void SortTexture(unsigned int index);
	void SortPoints();											//���ڵ������������� ���Ƚ�Y��Խ�͵ķ�ǰ�� Y����ͬ X��Խ�͵ķ�ǰ��

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