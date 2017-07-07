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
	int _Index;
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

class __IE_DLL__ IEPackerTexture:public IEObject
{
public:
	IEPackerTexture();
	virtual ~IEPackerTexture();
	virtual void Initialization(IEXml * xml);
	static IEPackerTexture * Create(IEXml * xml);

public:
	GLuint * GetTexture(float& beginX, float& beginY, float& sizeX, float& sizeY);

private:
	const char * LoadXML(IEXml * xml);
	void LoadTexture(const char * textureName);

public:
	GLuint * m_textureId;
	unsigned char m_groupCount;						//一共有多少个贴图组

	struct IETextureGroup * m_textureGroups;
};

IE_END

#endif