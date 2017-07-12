#define __IE_DLL_EXPORTS__
#include "IEwater.h"

IE_BEGIN

IEWater::IEWater()
{

}

IEWater::~IEWater()
{

}

void IEWater::Initialization(char * textureName)
{
	IESprite::Initialization(textureName);

	LoadShader();
}

IEWater * IEWater::Create(char * textureName)
{
	IEWater * terrain = new IEWater();
	terrain->Initialization(textureName);
	return terrain;
}

void IEWater::LoadShader()
{
	IEShader * shader = IEShader::Create("water.glsl");
	IENode::AttachShader(shader);
}

void IEWater::DrawNode()
{
	RunTexture();

	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());

		static float ia = 0.0f;
		ia += 0.005f;

		GLint borderValue2 = glGetUniformLocation(m_shader->GetShaderProgram(), "_Time");
		glUniform1f(borderValue2, ia);
	}
	if (m_texture)
	{
		GLuint * textureID = m_texture->GetTexture(m_textureUnit);
		glBindTexture(GL_TEXTURE_2D, *textureID);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
	glTexCoord2f(m_size[0] / 2, 0.0f); glVertex2f(m_size[0], 0);
	glTexCoord2f(m_size[0] / 2, m_size[1] / 2); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(0.0f, m_size[1] / 2); glVertex2f(0, m_size[1]);
	glEnd();

	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(NULL);
}

IE_END