#define __IE_DLL_EXPORTS__
#include "IEcolor.h"

IE_BEGIN

IEColor::IEColor()
{
	m_r = 0.0f;
	m_g = 0.0f;
	m_b = 0.0f;
	m_a = 1.0f;
}

IEColor::IEColor(IEColor &color)
{
	m_r = color.m_r;
	m_g = color.m_g;
	m_b = color.m_b;
	m_a = color.m_a;
}

IEColor::IEColor(const float &r, const float &g, const float &b)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = 1.0f;
}

IEColor::IEColor(const float &r, const float &g, const float &b, const float &a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

IEColor::~IEColor()
{

}

void IEColor::Initialization()
{

}

IEColor * IEColor::Create()
{
	IEColor * object = new IEColor();
	object->Initialization();
	return object;
}

IE_END