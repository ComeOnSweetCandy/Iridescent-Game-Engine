#define __IE_DLL_EXPORTS__
#include "IEpathGrid.h"

IE_BEGIN

IEPathGrid::IEPathGrid()
{

}

IEPathGrid::~IEPathGrid()
{

}

void IEPathGrid::Initialization()
{
	IENode::Initialization();

	ResetTunnel();
}

IEPathGrid * IEPathGrid::Create()
{
	IEPathGrid * grid = new IEPathGrid();
	grid->Initialization();
	return grid;
}

void IEPathGrid::ResetTunnel()
{
	for (int x = 0; x < PATH_PRECISION; x++)
	{
		for (int y = 0; y < PATH_PRECISION; y++)
		{
			//0xFF = 11111111
			m_tunnel[x][y] = 0xFF;
		}
	}
}

void IEPathGrid::DrawNode()
{
	glDisable(GL_BLEND);
	for (int x = 0; x < PATH_PRECISION; x++)
	{
		for (int y = 0; y < PATH_PRECISION; y++)
		{
			//glBegin(GL_LINES);

			//if (m_tunnel[x][y] & 0x1)
			//{
			//	glVertex2f(x*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));
			//	glVertex2f(x*(1.0f / PATH_PRECISION), (y + 1)*(1.0f / PATH_PRECISION));
			//}
			//if (m_tunnel[x][y] & 0x2)
			//{
			//	glVertex2f(x*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));
			//	glVertex2f((x + 1)*(1.0f / PATH_PRECISION), (y + 1)*(1.0f / PATH_PRECISION));
			//}
			//if (m_tunnel[x][y] & 0x4)
			//{
			//	glVertex2f(x*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));
			//	glVertex2f((x + 1)*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));
			//}
			//if (m_tunnel[x][y] & 0x8)
			//{
			//	glVertex2f(x*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));
			//	glVertex2f((x + 1)*(1.0f / PATH_PRECISION), (y - 1)*(1.0f / PATH_PRECISION));
			//}

			//glEnd();

			if (m_tunnel[x][y])
			{
				glPointSize(1.0f);
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else
			{
				glPointSize(4.0f);
				glColor3f(1.0f, 0.0f, 0.0f);
			}

			glBegin(GL_POINTS);

			glVertex2f(x*(1.0f / PATH_PRECISION), y*(1.0f / PATH_PRECISION));

			glEnd();
		}
	}
}

void IEPathGrid::SetGridGrid(int x, int y)
{
	m_gridGrid = IEGrid(x, y);
}

IEGrid IEPathGrid::GetGridGrid()
{
	return m_gridGrid;
}

void IEPathGrid::SetTunnel(int x, int y, unsigned char tunnel)
{
	m_tunnel[x][y] = m_tunnel[x][y] & tunnel;
}

unsigned char IEPathGrid::GetGridTunnelPassed(int x, int y)
{
	return m_tunnel[x][y];
}

IE_END