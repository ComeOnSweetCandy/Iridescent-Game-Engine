/***********************************
* name     : IEPackerTexture.h
* creater  : cosc
* info     : read packer texture
* date     : 2017/07/07
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PACKER_TEXTURE__
#define __IE_PACKER_TEXTURE__

#include "IETexture.h"
#include "IEXml.h"

IE_BEGIN

#define __IE_GROUP_RAND__ 0

struct IETextureFrap
{
	unsigned short int _X;
	unsigned short int _Y;
	unsigned short int _Width;
	unsigned short int _Height;
	float _End;
};

struct IETextureSame
{
	unsigned char _FrapsCount;
	IETextureFrap * _Fraps;
};

struct IETextureGroup
{
	char * _Name;
	char * _Assort;
	unsigned char _SameCount;
	IETextureSame * _Same;
};

struct IETextureUnitState
{
	GLuint _TextureID;
	unsigned char _GroupIndex;
	unsigned char _SameIndex;
	unsigned char _FrapIndex;
	float _CurTime;

	unsigned short int _X;
	unsigned short int _Y;
	unsigned short int _Width;
	unsigned short int _Height;

	float _BeginX;
	float _BeginY;
	float _EndX;
	float _EndY;
};

class __IE_DLL__ IEPackerTexture:public IEObject
{
public:
	IEPackerTexture();
	virtual ~IEPackerTexture();
	virtual void Initialization(IEXml * xml);
	virtual void Initialization(const char * textureName);
	static IEPackerTexture * Create(IEXml * xml);				//��ǰ��ʽ���ص���ͼ�ᱻ��Դ��������¼
	static IEPackerTexture * Create(const char * textureName);	//

public:
	void GetTexture(IETextureUnitState * unitState);
	void ChangeGroup(IETextureUnitState * textureUnitState, const char * groupName, unsigned char sameIndex);					//�޸ĵ�ǰ�������ͼ�� ��Ϊ���ܴ���ͬ����group�� ���Ժ������һ��index ����Ϊ0 �������һ��index
	void ChangeAssort(IETextureUnitState * textureUnitState, const char * assortName);

private:
	const char * LoadXML(IEXml * xml);							//��ȡxml
	void ForgeryXML(const char * textureName);					//�ڵ���ͼ�� α��һ��textureState
	void LoadTexture(const char * textureName);
	void FillTextureFrap(IETextureFrap& textureFrap, IEXml * xml);

public:
	GLuint * m_textureId;
	unsigned char m_groupCount;								//һ���ж��ٸ���ͼ��
	unsigned short int m_textureWidth;						//���
	unsigned short int m_textureHeight;						//�߶�

	struct IETextureGroup * m_textureGroups;
};

IE_END

#endif