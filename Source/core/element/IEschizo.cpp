#define __IE_DLL_EXPORTS__
#include "IEschizo.h"

IE_BEGIN

IESchizo::IESchizo()
{
	m_activeSprite = NULL;
	m_spriteCount = 0;
}

//IESchizo::IESchizo(IESprite * sprite, va_list ap)
//{
//	m_activeSprite = NULL;
//	m_spriteCount = 0;
//
//	IESprite * value = sprite;
//	while (value != NULL)
//	{
//		m_activeSprite = value;
//		m_spriteCount++;
//		value = va_arg(ap, IESprite *);
//	}
//}

IESchizo::~IESchizo()
{
	
}

void IESchizo::Initialization()
{

}

//IESchizo * IESchizo::Create(IESprite * sprites, ...)
//{
//	va_list ap;
//	va_start(ap, sprites);
//
//	IESchizo * object = new IESchizo(sprites, ap);
//	object->Initialization();
//	return object;
//
//	va_end(ap);
//	return object;
//}

IESchizo * IESchizo::Create()
{
	IESchizo * object = new IESchizo();
	object->Initialization();
	return object;
}

void IESchizo::DrawNode()
{
	if (m_activeSprite)
	{
		m_activeSprite->Visit();
	}
}

void IESchizo::AddSprite(const char * spriteName, IESprite * sprite)
{
	if (m_spritesArray[spriteName])
	{
		printf("this schizo has been adden in.\n");
	}
	else
	{
		m_spritesArray[spriteName] = sprite;
	}
}

void IESchizo::AddSprites(const char ** spritesName, IESprite ** sprites, unsigned int spriteNumber)
{
	for (unsigned int index = 0; index < spriteNumber; index++)
	{
		if (m_spritesArray[spritesName[index]])
		{
			printf("this schizo has been adden in.\n");
		}
		else
		{
			m_spritesArray[spritesName[index]] = sprites[index];
		}
	}
}

void IESchizo::ChangeAcitveSprite(const char * spriteName)
{
	if (m_spritesArray[spriteName])
	{
		m_activeSprite = (IESprite *)m_spritesArray[spriteName];
	}
}

IE_END