#define __IE_DLL_EXPORTS__
#include "IEnodeProtocol.h"

IE_BEGIN

IENodeProtocol::IENodeProtocol()
{
	m_rotate = 0.0f;
	m_scale = 1.0f;
	m_zIndex = 0;

	m_shader = NULL;
	m_display = true;

	SetDirection(0, -1);
	SetSize(1.0f, 1.0f);
	SetBackColor(1.0f, 1.0f, 1.0f, 1.0f);
}

IENodeProtocol::~IENodeProtocol()
{
	RemoveShader();
}

void IENodeProtocol::ChangeModelMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(m_translate[0], m_translate[1], 0.0f);
	glRotatef(m_rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(-m_size[0] * m_scale * m_anchor[0], -m_size[1] * m_scale * m_anchor[1], 0.0f);
	glScalef(m_scale, m_scale, 1.0f);
}

void IENodeProtocol::RevertModelMatrix()
{
	glPopMatrix();
}

void IENodeProtocol::SetRotate(const float &rotate)
{
	m_rotate = rotate;
}

void IENodeProtocol::SetScale(const float &scale)
{
	m_scale = scale;
}

void IENodeProtocol::SetZIndex(const float &zIndex)
{
	m_zIndex = zIndex;
}

void IENodeProtocol::SetAnchor(const float &x, const float &y)
{
	m_anchor[0] = x;
	m_anchor[1] = y;
}

void IENodeProtocol::SetTranslate(const float &x, const float &y)
{
	m_translate[0] = x;
	m_translate[1] = y;
}

void IENodeProtocol::SetDirection(const char &x, const char &y)
{
	m_direction[0] = x;
	m_direction[1] = y;
}

void IENodeProtocol::SetSize(const float &x, const float &y)
{
	m_size[0] = x;
	m_size[1] = y;
}

float * IENodeProtocol::GetTranslate()
{
	return m_translate;
}

float * IENodeProtocol::GetSize()
{
	return m_size;
}

char * IENodeProtocol::GetDirection()
{
	return m_direction;
}

float& IENodeProtocol::GetZIndex()
{
	return m_zIndex;
}

void IENodeProtocol::AttachShader(IEShader * shader)
{
	m_shader = shader;
	m_shader->Retain();
}

void IENodeProtocol::RemoveShader()
{
	if (m_shader)
	{
		m_shader->Discard();
		m_shader = NULL;
	}
}

bool& IENodeProtocol::GetDisplay()
{
	return m_display;
}

void IENodeProtocol::SetDisplay(bool display)
{
	m_display = display;
}

void IENodeProtocol::SetBackColor(float r, float g, float b, float a)
{
	m_backColor[0] = r;
	m_backColor[1] = g;
	m_backColor[2] = b;
	m_backColor[3] = a;
}

IE_END