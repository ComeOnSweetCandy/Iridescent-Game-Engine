#define __IE_DLL_EXPORTS__
#include "IEvector.h"

#include "IEgrid.h"

IE_BEGIN

IEVector::IEVector()
{
	this->m_x = 0;
	this->m_y = 0;
}

IEVector::IEVector(float value)
{
	this->m_x = value;
	this->m_y = value;
}

IEVector::IEVector(float x, float y)
{
	this->m_x = x;
	this->m_y = y;
}

IEVector::IEVector(IEGrid &grid)
{
	this->m_x = grid.m_x;
	this->m_y = grid.m_y;
}

IEVector::~IEVector()
{

}

IEVector IEVector::operator + (const IEVector &vector) const
{
	IEVector newV;
	newV.m_x = this->m_x + vector.m_x;
	newV.m_y = this->m_y + vector.m_y;
	return newV;
}

IEVector IEVector::operator - (const IEVector &vector) const
{
	IEVector newV;
	newV.m_x = this->m_x - vector.m_x;
	newV.m_y = this->m_y - vector.m_y;
	return newV;
}

IEVector IEVector::operator *(const int &value) const
{
	IEVector newV;
	newV.m_x = this->m_x * value;
	newV.m_y = this->m_y * value;
	return newV;
}

IEVector IEVector::operator *(const unsigned int &value) const
{
	IEVector newV;
	newV.m_x = this->m_x * value;
	newV.m_y = this->m_y * value;
	return newV;
}

IEVector IEVector::operator /(const int &value) const
{
	IEVector newV;
	newV.m_x = this->m_x / value;
	newV.m_y = this->m_y / value;
	return newV;
}

IEVector IEVector::operator /(const unsigned int &value) const
{
	IEVector newV;
	newV.m_x = this->m_x / value;
	newV.m_y = this->m_y / value;
	return newV;
}

IEVector IEVector::operator *(const float &value) const
{
	IEVector newV;
	newV.m_x = this->m_x * value;
	newV.m_y = this->m_y * value;
	return newV;
}

IEVector operator * (float value, const IEVector &vector)
{ 
	return IEVector(vector.m_x * value, vector.m_y * value);
}

IEVector IEVector::operator /(const float &value) const
{
	IEVector newV;
	newV.m_x = this->m_x / value;
	newV.m_y = this->m_y / value;
	return newV;
}

IEVector IEVector::operator /(IEVector &vector) const
{
	IEVector newV;
	newV.m_x = m_x / vector.m_x;
	newV.m_y = m_y / vector.m_y;
	return newV;
}

IEVector IEVector::operator -(void) const
{
	return IEVector(-m_x, -m_y);
}

void IEVector::operator =(const IEVector &vector)
{
	this->m_x = vector.m_x;
	this->m_y = vector.m_y;
}

void IEVector::operator =(const float &value)
{
	this->m_x = value;
	this->m_y = value;
}

bool IEVector::operator ==(const IEVector &vector)
{
	if (m_x == vector.m_x && m_y == vector.m_y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float IEVector::CrossProduct(IEVector &x, IEVector &y)
{
	return x.m_x * y.m_y - x.m_y * y.m_x;
}

float IEVector::DotProduct(const IEVector &x, const IEVector &y)
{
	return x.m_x * y.m_x + x.m_y * y.m_y;
}

float IEVector::operator ^(const IEVector &vector) const
{
	return m_x * vector.m_y - m_y * vector.m_x;
}

float IEVector::operator *(const IEVector &vector) const
{
	return m_x * vector.m_x + m_y * vector.m_y;
}

IEVector IEVector::operator - (const IEGrid &grid) const
{
	IEVector newV;
	newV.m_x = this->m_x - (float)grid.m_x;
	newV.m_y = this->m_y - (float)grid.m_y;
	return newV;
}

float IEVector::Length() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

void IEVector::Abs()
{
	if (m_x < 0.0f)
	{
		m_x = -m_x;
	}
	if (m_y < 0.0f)
	{
		m_y = -m_y;
	}
}

void IEVector::Normalize()
{
	float length = Length();
	m_x /= length;
	m_y /= length;
}

IE_END