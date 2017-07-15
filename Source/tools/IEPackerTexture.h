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

struct IETextureFrap
{
	unsigned short int _X;
	unsigned short int _Y;
	unsigned short int _Width;
	unsigned short int _Height;
	float _End;
};

struct IETextureGroup
{
	char * _Name;
	unsigned char _FrapsCount;
	IETextureFrap * _Fraps;
};

struct IETextureUnitState
{
	GLuint _TextureID;
	unsigned char _GroupIndex;
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
	static IEPackerTexture * Create(IEXml * xml);				//当前方式加载的贴图会被资源管理器记录
	static IEPackerTexture * Create(const char * textureName);	//

public:
	void GetTexture(IETextureUnitState * unitState);
	void ChangeGroup(IETextureUnitState * textureUnitState, const char * groupName, unsigned char sameIndex = 0);					//修改当前激活的贴图组 因为可能存在同名的group组 所以后面加上一个index

private:
	const char * LoadXML(IEXml * xml);							//读取xml
	void ForgeryXML(const char * textureName);					//在单贴图下 伪造一份textureState
	void LoadTexture(const char * textureName);
	void FillTextureFrap(IETextureFrap& textureFrap, IEXml * xml);

public:
	GLuint * m_textureId;
	unsigned char m_groupCount;								//一共有多少个贴图组
	unsigned short int m_textureWidth;						//宽度
	unsigned short int m_textureHeight;						//高度

	struct IETextureGroup * m_textureGroups;
};

IE_END

#endif