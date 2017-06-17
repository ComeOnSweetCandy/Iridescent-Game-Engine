#define __IE_DLL_EXPORTS__
#include "IElayer.h"

IE_BEGIN 

IELayer::IELayer()
{

}

IELayer::~IELayer()
{

}

void IELayer::Initialization()
{
	IENode::Initialization();
}

IELayer * IELayer::Create()
{
	IELayer * layer = new IELayer();
	layer->Initialization();
	return layer;
}

void IELayer::DrawNode()
{
	//if (m_displayBackground) DrawBackground();
	//if (m_displayBorder) DrawBorder();
}

void IELayer::DrawBackground()
{
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
		//GLint borderValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_borderWidth");
		//glUniform1f(borderValue, m_borderWidth);
		GLint boxWidthValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_boxWidth");
		glUniform1f(boxWidthValue, m_size[0]);
		GLint boxHeightValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_boxHeight");
		glUniform1f(boxHeightValue, m_size[1]);
		GLint boxc = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_boxCenter");
		float center[2] = { 1.7f, 1.0f };
		glUniform2fv(boxc, 1, center);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor3f(m_backgroundColor.m_r, m_backgroundColor.m_g, m_backgroundColor.m_b);
	glColor4f(0.0f, 1.0f, 2.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(m_size[0], 0);
	glVertex2f(m_size[0], m_size[1]);
	glVertex2f(0, m_size[1]);
	glEnd();
	glDisable(GL_BLEND);

	glUseProgram(NULL);
}

void IELayer::DrawBorder()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glBlendFunc(GL_ONE,GL_ZERO);
	//glColor4f(m_borderColor.m_r, m_borderColor.m_g, m_borderColor.m_b, m_borderColor.m_a); 这里可以使用一个公共的颜色
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(m_size[0], 0);
	glVertex2f(m_size[0], m_size[1]);
	glVertex2f(0, m_size[1]);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

IE_END