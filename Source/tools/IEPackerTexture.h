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
	int _X;
	int _Y;
	int _Width;
	int _Height;
	float _End;
};

struct IETextureGroup
{
	char * _Name;
	unsigned char _FrapsCount;
	IETextureFrap *_Fraps;
};

struct IETextureUnitState
{
	unsigned char _GroupIndex;
	unsigned char _FrapIndex;
	float _CurTime;

	int _X;
	int _Y;
	int _Width;
	int _Height;

	float _BeginX;
	float _BeginY;
	float _SizeX;
	float _SizeY;
};

class __IE_DLL__ IEPackerTexture:public IEObject
{
public:
	IEPackerTexture();
	virtual ~IEPackerTexture();
	virtual void Initialization(IEXml * xml);
	static IEPackerTexture * Create(IEXml * xml);

public:
	GLuint * GetTexture(IETextureUnitState * unitState);

private:
	const char * LoadXML(IEXml * xml);
	void LoadTexture(const char * textureName);
	void FillTextureFrap(IETextureFrap& textureFrap, IEXml * xml);

public:
	GLuint * m_textureId;
	unsigned char m_groupCount;						//一共有多少个贴图组

	struct IETextureGroup * m_textureGroups;
};

IE_END

#endif