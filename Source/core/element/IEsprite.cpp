#define __IE_DLL_EXPORTS__
#include "IEsprite.h"

IE_BEGIN

IESprite::IESprite()
{
	m_shader = NULL;
	m_tex = NULL;
	m_texUnitState = NULL;
}

IESprite::~IESprite()
{
	RemoveTexture();

	__IE_DELETE__(m_texUnitState);
}

void IESprite::Initialization(const char * textureName)
{
	IEElement::Initialization();

	m_texUnitState = new IETextureUnitState();
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

void IESprite::DrawNode()
{
	RunTexture();

	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
	}
	if (m_tex)
	{
		GLuint * textureID = m_tex->GetTexture(m_texUnitState);
		glBindTexture(GL_TEXTURE_2D, *textureID);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(m_texUnitState->_BeginX, m_texUnitState->_BeginY); glVertex2f(0, 0);
	glTexCoord2f(m_texUnitState->_EndX, m_texUnitState->_BeginY); glVertex2f(m_size[0], 0);
	glTexCoord2f(m_texUnitState->_EndX, m_texUnitState->_EndY); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(m_texUnitState->_BeginX, m_texUnitState->_EndY); glVertex2f(0, m_size[1]);
	glEnd();

	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(NULL);
}

void IESprite::ReckonSize()
{
	m_size[0] = float(m_tex->m_textureWidth) / m_unitPixels;
	m_size[1] = float(m_tex->m_textureHeight) / m_unitPixels;
}

void IESprite::ChangeTexture(const char * textureName)
{
	if (textureName == NULL)
	{
		return;
	}

	RemoveTexture();

	m_tex = IEPackerTexture::Create(textureName);
	m_tex->Retain();
	m_tex->ChangeGroup(m_texUnitState, "default");

	ReckonSize();
}

void IESprite::ChangeTexture(IEPackerTexture * packerTexture)
{
	if (packerTexture == NULL)
	{
		return;
	}

	RemoveTexture();

	m_tex = packerTexture;
	m_tex->Retain();
	m_tex->ChangeGroup(m_texUnitState, "f");

	ReckonSize();
}

void IESprite::ChangeGroup(const char * textureName, unsigned int times)
{
	//ChangeTexture(textureName);
	//m_textureState->m_temporaryRun = true;
	if (m_tex)
	{
		m_tex->ChangeGroup(m_texUnitState, textureName);
	}
}

void IESprite::RemoveTexture()
{
	if (m_tex)
	{
		m_tex->Discard();
		m_tex = NULL;
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