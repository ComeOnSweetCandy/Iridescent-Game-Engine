#define __IE_DLL_EXPORTS__
#include "IEsprite.h"

IE_BEGIN

IESprite::IESprite()
{
	m_shader = NULL;
	m_texture = NULL;
	m_textureUnit = NULL;
}

IESprite::~IESprite()
{
	RemoveTexture();

	__IE_DELETE__(m_textureUnit);
}

void IESprite::Initialization(const char * textureName)
{
	IEElement::Initialization();

	m_textureUnit = new IETextureUnitState();
	IESprite::ChangeTexture(textureName);
}

IESprite * IESprite::Create()
{
	return IESprite::Create(NULL);
}

IESprite * IESprite::Create(const char * textureName)
{
	IESprite * sprite = new IESprite();
	sprite->Initialization(textureName);
	return sprite;
}

void IESprite::PreVisit()
{
	if (m_texture)
	{
		m_texture->GetTexture(m_textureUnit);
	}

	ReckonSize();
}

void IESprite::DrawNode()
{
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
	}

	static float drawX, drawY;		//最终定义绘制的方向的
	drawX = m_drawDirection[0] ? 0 : m_size[0];
	drawY = m_drawDirection[1] ? 0 : m_size[1];

	glBindTexture(GL_TEXTURE_2D, m_textureUnit->_TextureID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBegin(GL_QUADS);
	//glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_BeginY); glVertex2f(0, 0);
	//glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_BeginY); glVertex2f(m_size[0], 0);
	//glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_EndY); glVertex2f(m_size[0], m_size[1]);
	//glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_EndY); glVertex2f(0, m_size[1]);

	glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_BeginY); glVertex2f(drawX, drawY);
	glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_BeginY); glVertex2f(m_size[0] - drawX, drawY);
	glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_EndY); glVertex2f(m_size[0] - drawX, m_size[1] - drawY);
	glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_EndY); glVertex2f(drawX, m_size[1] - drawY);
	glEnd();

	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(NULL);
}

void IESprite::ReckonSize()
{
	//m_size[0] = float(m_texture->m_textureWidth) / m_unitPixels;
	//m_size[1] = float(m_texture->m_textureHeight) / m_unitPixels;
	m_size[0] = float(m_textureUnit->_Width) / m_unitPixels;
	m_size[1] = float(m_textureUnit->_Height) / m_unitPixels;
}

void IESprite::ChangeTexture(const char * textureName)
{
	if (textureName == NULL)
	{
		return;
	}

	RemoveTexture();

	m_texture = IEPackerTexture::Create(textureName);
	m_texture->Retain();
}

void IESprite::ChangeTexture(IEPackerTexture * packerTexture)
{
	if (packerTexture == NULL)
	{
		return;
	}

	RemoveTexture();

	m_texture = packerTexture;
	m_texture->Retain();
}

void IESprite::ChangeAssort(const char * assortName)
{
	if (m_textureUnit)
	{
		//拷贝一份 分类组名
		strcpy(m_textureUnit->_AssortName, assortName);

		if (m_textureUnit->_TextureID != 0)
		{
			//重新获取新的贴图组
			m_texture->ChangeGroup(m_textureUnit, m_texture->m_textureGroups[m_textureUnit->_GroupIndex]._Name, m_textureUnit->_SameIndex);
		}
	}
}

void IESprite::ChangeGroup(const char * groupName, unsigned int sameIndex)
{
	if (m_texture)
	{
		//获取新的贴图组
		m_texture->ChangeGroup(m_textureUnit, groupName, sameIndex);

		//重新计算一些东西
		ReckonSize();
	}
}

void IESprite::ChangeGroup(const char * groupName, unsigned int sameIndex, unsigned int playTimes, IESprite * sprite, IEFunctionTexturePlayEnded playEndedFunction)
{
	if (m_texture)
	{
		//获取新的贴图组
		m_texture->ChangeGroup(m_textureUnit, groupName, sameIndex, playTimes, sprite, playEndedFunction);
	}
}

IETextureUnitState * IESprite::GetTextureUnitState()
{
	return m_textureUnit;
}

IEPackerTexture * IESprite::GetTexture()
{
	return m_texture;
}

void IESprite::RemoveTexture()
{
	if (m_texture)
	{
		m_texture->Discard();
		m_texture = NULL;
	}
}

bool IESprite::TriggerFrap()
{
	//return m_textureState->m_triggerFrap;
	return true;
}

bool IESprite::EndFrap()
{
	//return m_textureState->;
	return false;
}

IE_END