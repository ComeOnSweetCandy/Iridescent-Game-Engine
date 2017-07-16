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
	void ChangeTexture(const char * textureName);							//ֱ�Ӹ�����ͼ
	void ChangeTexture(IEPackerTexture * packerTexture);					//ֱ�Ӹ�����ͼ
	void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);	//������ͼ�� Ĭ��ʹ�õ�һ��texture group
	IEPackerTexture * GetTexture();											//��ȡ��ͼ
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