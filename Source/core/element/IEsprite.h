/***********************************
* name     : IEsprite.h
* creater  : cosc
* info     : sprite
* date     : 2016/11/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SPRITE__
#define __IE_SPRITE__

#include "IEelement.h"
#include "../../tools/IEPackerTexture.h"

IE_BEGIN

class __IE_DLL__ IESprite :public IEElement
{
public:
	IESprite();
	virtual ~IESprite();
	virtual void Initialization(const char * textureName);
	static IESprite * Create();
	static IESprite * Create(const char * textureName);

protected:
	virtual void PreVisit();
	virtual void DrawNode();
	virtual void ReckonSize();

public:
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);	//更换贴图组 默认使用第一个texture group

	void ChangeTexture(const char * textureName);									//直接更换贴图
	void ChangeTexture(IEPackerTexture * packerTexture);							//直接更换贴图
	IETextureUnitState * GetTextureUnitState();										//获取贴图组的序号
	IEPackerTexture * GetTexture();													//获取贴图
	void RemoveTexture();
	;
	virtual bool TriggerFrap();
	virtual bool EndFrap();

protected:
	IEPackerTexture * m_texture;
	IETextureUnitState * m_textureUnit;
};

IE_END

#endif