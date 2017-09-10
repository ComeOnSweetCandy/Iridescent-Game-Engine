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
	DrawFire();
	DrawLight();
}

void IETorch::DrawLight()
{
	glPushMatrix();
	glTranslatef(m_size[0] / 2, m_size[1] / 2, 0.0f);

	glDisable(GL_TEXTURE);
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());

		GLint radius = glGetUniformLocation(m_shader->GetShaderProgram(), "radius");
		glUniform1f(radius, m_distance);

		GLint intension = glGetUniformLocation(m_shader->GetShaderProgram(), "intension");
		glUniform1f(intension, m_intension);

		GLint baseLight = glGetUniformLocation(m_shader->GetShaderProgram(), "baseLight");
		glUniform1f(baseLight, m_baseLight);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor4f(m_lightColor.m_r, m_lightColor.m_g, m_lightColor.m_b, m_lightColor.m_a);
	glBegin(GL_QUADS);
	glVertex2f(-m_distance * 2, -m_distance * 2);
	glVertex2f(m_distance * 2, -m_distance * 2);
	glVertex2f(m_distance * 2, m_distance * 2);
	glVertex2f(-m_distance * 2, m_distance * 2);
	glEnd();

	glDisable(GL_BLEND);
	glUseProgram(NULL);

	glPopMatrix();
}

void IETorch::DrawFire()
{
	//if (m_shader)
	//{
	//	glUseProgram(m_shader->GetShaderProgram());
	//}

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