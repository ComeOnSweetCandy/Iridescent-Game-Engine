#define __IE_DLL_EXPORTS__
#include "IEprocessBar.h"

IE_BEGIN

IEProcessBar::IEProcessBar()
{
	IEShader * shader = IEShader::Create("border.glsl"); //*** shader compile 80000 ***//
	AttachShader(shader);
}

IEProcessBar::~IEProcessBar()
{
	RemoveShader();
}

void IEProcessBar::Initialization(float process)
{
	IEElement::Initialization();

	m_process = process;
	m_borderWidth = 1.0f;
}

IEProcessBar * IEProcessBar::Create(float process)
{
	IEProcessBar * node = new IEProcessBar();
	node->Initialization(process);
	return node;
}

void IEProcessBar::SetProcess(float process)
{
	m_process = process;
}

float & IEProcessBar::GetProcess()
{
	return m_process;
}

void IEProcessBar::DrawNode()
{
	DrawProcess();
	DrawBorder();
}

void IEProcessBar::DrawProcess()
{
	glUseProgram(NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glColor4f(m_backColor[0], m_backColor[1], m_backColor[2], m_backColor[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0 + m_borderWidth, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2f((m_size[0] - 2 * m_borderWidth) * m_process + m_borderWidth, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f((m_size[0] - 2 * m_borderWidth) * m_process + m_borderWidth, m_size[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0 + m_borderWidth, m_size[1]);
	glEnd();
}

void IEProcessBar::DrawBorder()
{
	if (m_shader)
	{
		glUseProgram(m_shader->GetShaderProgram());
	}
	GLint borderValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_borderWidth");	
	glUniform1f(borderValue, m_borderWidth);
	GLint boxWidthValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_boxWidth");
	glUniform1f(boxWidthValue, m_size[0]);
	GLint boxHeightValue = glGetUniformLocation(m_shader->GetShaderProgram(), "glsl_boxHeight");
	glUniform1f(boxHeightValue, m_size[1]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(m_size[0], 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(m_size[0], m_size[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, m_size[1]);
	glEnd();

	glDisable(GL_BLEND);
	glUseProgram(NULL);
}

IE_END