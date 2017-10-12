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
	virtual void ChangeAssort(const char * assortName);																								//������ͼ�����
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex = 1);																	//������ͼ�� Ĭ��ʹ�õ�һ��texture group
	virtual void ChangeGroup(const char * groupName, unsigned int sameIndex, unsigned int playTimes, IEObject * object, IEFunctionTexturePlayFinished playEndedFunction);		//������ͼ�� ��ִ��һ������ �ص�����

	void ChangeTexture(const char * textureName);									//ֱ�Ӹ�����ͼ
	void ChangeTexture(IEPackerTexture * packerTexture);							//ֱ�Ӹ�����ͼ
	IETextureUnitState * GetTextureUnitState();										//��ȡ��ͼ������
	IEPackerTexture * GetTexture();													//��ȡ��ͼ
	void RemoveTexture();

	virtual bool TriggerFrap();
	virtual bool EndFrap();

protected:
	IEPackerTexture * m_texture;
	IETextureUnitState * m_textureUnit;
};

IE_END

#endif