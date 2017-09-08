#define __IE_DLL_EXPORTS__
#include "IETorch.h"

IE_BEGIN


IETorch::IETorch()
{

}

IETorch::~IETorch()
{

}

void IETorch::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);

	SetProperty();
}

IETorch * IETorch::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IETorch * thing = new IETorch();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IETorch::Update()
{
	//呼吸效果
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

void IETorch::DrawNode()
{
	IEThing::DrawNode();
	DrawFire();
	DrawLight();
}

void IETorch::DrawLight()
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

void IETorch::DrawFire()
{
	IEThing::DrawNode();

	//if (m_texture)
	//{
	//	m_texture->GetTexture(m_textureUnit);
	//	glBindTexture(GL_TEXTURE_2D, m_textureUnit->_TextureID);
	//}

	//glEnable(GL_BLEND);

	//glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
	//glTexCoord2f(1.0f, 0.0f); glVertex2f(m_size[0], 0);
	//glTexCoord2f(1.0f, 1.0f); glVertex2f(m_size[0], m_size[1]);
	//glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_size[1]);
	//glEnd();
	//glDisable(GL_BLEND);

	//glBindTexture(GL_TEXTURE_2D, NULL);
}

void IETorch::SetProperty()
{
	//读取shader 然后加载
	IEShader * shader = IEShader::Create(m_XML->FindChild("script")->ValueString());
	IENode::AttachShader(shader);

	//读取各项属性
	m_distance = m_XML->FindChild("property")->FindChild("distance")->ValueFloat();
	m_baseLight = m_XML->FindChild("property")->FindChild("baseLight")->ValueFloat();
	m_intension = m_XML->FindChild("property")->FindChild("intension")->ValueFloat();

	IEString * colorString = m_XML->FindChild("property")->FindChild("intension")->Value();
	m_lightColor = IEColor(1.0f, 0.0f, 0.0f, 1.0f);

}

IE_END