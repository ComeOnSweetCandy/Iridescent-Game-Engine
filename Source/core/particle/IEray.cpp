#define __IE_DLL_EXPORTS__
#include "IEray.h"

IE_BEGIN

IERay::IERay()
{
	m_rayWidth = 0.0f;
	m_rayLength = 0.0f;
	m_rayRotate = 0.0f;
}

IERay::~IERay()
{

}

void IERay::Initialization(char * textureName, float rayLength, float rayRotaf)
{
	IEParticle::Initialization(textureName);

	SetRayLength(rayLength);
	SetRayRotate(rayRotaf);
}

IERay * IERay::Create(char * textureName, float rayLength, float rayRotaf)
{
	IERay * particle = new IERay();
	particle->Initialization(textureName, rayLength, rayRotaf);
	return particle;
}

void IERay::SetRayLength(float rayLength)
{
	m_rayLength = rayLength;
	m_size[0] = rayLength;
}

void IERay::SetRayRotate(float rayRotate)
{
	m_rayRotate = rayRotate;

	IENode::SetRotate(m_rayRotate);
}

void IERay::DrawNode()
{
	//IEParticle::DrawNode();

	RunTexture();
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
	}
	if (m_texture)
	{
		GLuint * textureID = m_texture->GetTexturesId();
		glBindTexture(GL_TEXTURE_2D, textureID[m_textureState->m_curTextureIndex]);
	}

	glEnable(GL_BLEND);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
	glTexCoord2f(m_size[0], 0.0f); glVertex2f(m_size[0], 0);
	glTexCoord2f(m_size[0], 1.0f); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_size[1]);
	glEnd();
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glUseProgram(NULL);
}

IE_END