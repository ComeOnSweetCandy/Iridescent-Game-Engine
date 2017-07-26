#define __IE_DLL_EXPORTS__
#include "IEPath.h"

IE_BEGIN

IEPath::IEPath()
{

}

IEPath::~IEPath()
{

}

void IEPath::Initialization()
{
	IENode::Initialization();

	ResetTunnel();
}

IEPath * IEPath::Create()
{
	IEPath * grid = new IEPath();
	grid->Initialization();
	return grid;
}

void IEPath::ResetTunnel()
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

void IEPath::DrawNode()
{
	return;

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

void IEPath::SetGridGrid(int x, int y)
{
	m_gridGrid = IEGrid(x, y);
}

IEGrid IEPath::GetGridGrid()
{
	return m_gridGrid;
}

void IEPath::SetTunnel(int x, int y, unsigned char tunnel)
{
	m_tunnel[x][y] = m_tunnel[x][y] & tunnel;
}

unsigned char IEPath::GetGridTunnelPassed(int x, int y)
{
	return m_tunnel[x][y];
}

IE_END