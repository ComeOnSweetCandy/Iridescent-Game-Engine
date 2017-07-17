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
	RunTexture();

	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
	}

	glBindTexture(GL_TEXTURE_2D, m_textureUnit->_TextureID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_BeginY); glVertex2f(0, 0);
	glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_BeginY); glVertex2f(m_size[0], 0);
	glTexCoord2f(m_textureUnit->_EndX, m_textureUnit->_EndY); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(m_textureUnit->_BeginX, m_textureUnit->_EndY); glVertex2f(0, m_size[1]);
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
	ChangeGroup("default");

	ReckonSize();
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
	ChangeGroup("default");

	ReckonSize();
}

void IESprite::ChangeGroup(const char * groupName, unsigned int sameIndex)
{
	if (m_texture)
	{
		m_texture->ChangeGroup(m_textureUnit, groupName, sameIndex);
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

void IESprite::RunTexture()
{
	//if (m_texture && m_textureState && m_textureState->m_allow && m_texture->m_textureFramesCount > 1)
	//{
	//	m_textureState->m_curTextureTime = m_textureState->m_curTextureTime + IETime::Share()->GetLastFrapPassingTime();
	//	if (m_textureState->m_curTextureTime >= m_texture->m_timeAxis[m_textureState->m_curTextureIndex])
	//	{
	//		m_textureState->m_curTextureIndex++;

	//		if (m_textureState->m_curTextureIndex + 1 == m_texture->m_triggerAxis)
	//		{
	//			//该帧为触发帧
	//			m_textureState->m_triggerFrap = true;
	//		}
	//	}
	//	if (m_textureState->m_curTextureIndex >= m_texture->m_textureFramesCount)
	//	{
	//		//播放完成一圈
	//		if (m_textureState->m_temporaryRun)
	//		{
	//			m_textureState->m_temporaryRun = false;
	//			TemporaryTextureEnd();
	//		}
	//		else
	//		{
	//			m_textureState->m_curTextureTime = 0.0f;
	//			m_textureState->m_curTextureIndex = 0;
	//		}
	//	}
	//}
}

bool IESprite::IsTriggerFrap()
{
	//return m_textureState->m_triggerFrap;
	return true;
}

bool IESprite::IsEndFrap()
{
	//return m_textureState->;
	return false;
}

void IESprite::TemporaryTextureEnd()
{
	//m_textureState->m_allow = false;
	//m_textureState->m_curTextureIndex--;
}

IE_END