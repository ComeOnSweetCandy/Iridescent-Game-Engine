#define __IE_DLL_EXPORTS__
#include "IEfire.h"

IE_BEGIN


IEFire::IEFire()
{
	m_intension = 3.0f;
	m_distance = 5.0f;
}

IEFire::~IEFire()
{

}

void IEFire::Initialization(unsigned int thingID, float distance)
{
	IEThing::Initialization(thingID);
	IESprite::ChangeTexture("fire/body.png");

	IEShader * shader = IEShader::Create("fire.glsl");
	IENode::AttachShader(shader);

	SetLightDistance(distance);
}

IEFire * IEFire::Create(unsigned int thingID, float distance)
{
	IEFire * light = new IEFire();
	light->Initialization(thingID, distance);
	return light;
}

void IEFire::Update()
{
	//ºôÎüÐ§¹û
	static float maxMulti = 1.1f;
	static float minMulti = 0.9f;

	static float curMulti = 1.0f;
	static float beginDistance = m_distance;
	static float beginIntension = m_intension;

	static int value = 1;
	static float speed = 0.001f;

	m_distance = beginDistance * curMulti;
	m_intension = beginIntension * curMulti;
	curMulti = curMulti + speed * value;

	if (curMulti > maxMulti)
	{
		value = -1;
	}
	else if (curMulti < minMulti)
	{
		value = 1;
	}
}

void IEFire::DrawNode()
{
	DrawLight();
	DrawFire();
}

void IEFire::DrawLight()
{
	glPushMatrix();
	glTranslatef(-m_distance + m_size[0] / 2, -m_distance + m_size[1] / 2, 0.0f);

	glDisable(GL_TEXTURE);
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());

		GLint radius = glGetUniformLocation(m_shader->GetShaderProgram(), "radius");
		glUniform1f(radius, m_distance);

		GLint intension = glGetUniformLocation(m_shader->GetShaderProgram(), "intension");
		glUniform1f(intension, m_intension);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ONE);

	glColor4f(m_lightColor.m_r, m_lightColor.m_g, m_lightColor.m_b, m_lightColor.m_a);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(m_distance * 2.0f, 0);
	glVertex2f(m_distance * 2.0f, m_distance * 2.0f);
	glVertex2f(0, m_distance * 2.0f);
	glEnd();

	glDisable(GL_BLEND);
	glUseProgram(NULL);

	glPopMatrix();
}

void IEFire::DrawFire()
{
	//RunTexture();

	if (m_texture)
	{
		m_texture->GetTexture(m_textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_textureUnit->_TextureID);
	}

	glEnable(GL_BLEND);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(m_size[0], 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_size[1]);
	glEnd();
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void IEFire::SetLightColor(float r, float g, float b, float a)
{
	m_lightColor = IEColor(r, g, b, a);
}

void IEFire::SetLightDistance(float distance)
{
	m_distance = distance;
}

void IEFire::SetLightIntension(float intension)
{
	m_intension = intension;
}

IE_END