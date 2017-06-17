#define __IE_DLL_EXPORTS__
#include "IEgrid.h"
#include "IEvector.h"

IE_BEGIN

IEGrid::IEGrid()
{
	m_x = 0;
	m_y = 0;
}

IEGrid::IEGrid(IEGrid &grid)
{
	m_x = grid.m_x;
	m_y = grid.m_y;
}

IEGrid::IEGrid(IEVector &vector)
{
	m_x = (int)vector.m_x;
	m_y = (int)vector.m_y;
}

IEGrid::IEGrid(int x, int y)
{
	m_x = x;
	m_y = y;
}

IEGrid::IEGrid(int value)
{
	m_x = m_y = value;
}

IEGrid::~IEGrid()
{

}

void IEGrid::Initialization()
{

}

IEGrid * IEGrid::Create(int x, int y)
{
	IEGrid * grid = new IEGrid(x, y);
	return grid;
}

IEGrid IEGrid::operator +(IEGrid & grid)
{
	return IEGrid(m_x + grid.m_x, m_y + grid.m_y);
}

IEGrid IEGrid::operator -(IEGrid & grid)
{
	return IEGrid(m_x - grid.m_x, m_y - grid.m_y);
}

IEGrid IEGrid::operator *(int value)
{
	return IEGrid(m_x * value, m_y * value);
}

IEVector IEGrid::operator *(float value)
{
	return IEVector(m_x * value, m_y * value);
}

IEGrid IEGrid::operator /(int value)
{
	return IEGrid(m_x / value, m_y / value);
}

IEGrid IEGrid::operator %(int value)
{
	return IEGrid(m_x % value, m_y % value);
}

bool IEGrid::operator ==(IEGrid & grid)
{
	if (m_x == grid.m_x && m_y == grid.m_y)
	{
		return true;
	}
	return false;
}

bool IEGrid::operator !=(IEGrid & grid)
{
	if (m_x != grid.m_x || m_y != grid.m_y)
	{
		return true;
	}
	return false;
}

IEVector IEGrid::operator +(IEVector &vector)
{
	IEVector newVector = IEVector(m_x + vector.m_x, m_y + vector.m_y);
	return newVector;
}

IEGrid IEGrid::Absolute()
{
	int mx = m_x > 0 ? m_x : -m_x;
	int my = m_y > 0 ? m_y : -m_y;
	return IEGrid(mx, my);
}

void IEGrid::Abs()
{
	m_x = m_x > 0 ? m_x : -m_x;
	m_y = m_y > 0 ? m_y : -m_y;
}

IE_END