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

//typedef struct ieTextureState
//{
//	ieTextureState()
//	{
//		Reset();
//	};
//	void Reset()
//	{
//		m_curTextureIndex = 0;
//		m_curTextureTime = 0.0f;
//		m_temporaryRun = false;
//		m_triggerFrap = false;
//		m_allow = true;
//	}
//	unsigned int m_curTextureIndex;
//	float m_curTextureTime;
//	bool m_temporaryRun;
//	bool m_triggerFrap;
//	bool m_allow;
//}IETextureState;

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

	void RunTexture();

public:
	void ChangeTexture(const char * textureName);							//直接更换贴图
	void ChangeTexture(IEPackerTexture * packerTexture);					//直接更换贴图
	void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);	//更换贴图组 默认使用第一个texture group
	IEPackerTexture * GetTexture();											//获取贴图
	void RemoveTexture();
	
	virtual void TemporaryTextureEnd();
	virtual bool IsTriggerFrap();
	virtual bool IsEndFrap();

protected:
	IEPackerTexture * m_texture;
	IETextureUnitState * m_textureUnit;
};

IE_END

#endif