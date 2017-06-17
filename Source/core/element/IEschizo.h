/***********************************
* name     : IEcshizo.h
* creater  : cosc
* info     : sprite assemble
* date     : 2016/11/29
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SCHIZO__
#define __IE_SCHIZO__

#include "IEElement.h"
#include "IEsprite.h"

IE_BEGIN

class IESchizo:public IEElement
{
public:
	IESchizo();
	~IESchizo();
	virtual void Initialization();
	static IESchizo * Create();
	
public:
	virtual void DrawNode();
	void AddSprite(const char * spriteName, IESprite * sprite);
	void AddSprites(const char ** spriteName, IESprite ** sprite, unsigned int spriteNumber);
	void ChangeAcitveSprite(const char * spriteName);

private:
	IEDictionary m_spritesArray;
	IESprite * m_activeSprite;
	unsigned int m_spriteCount;
};

IE_END

#endif