#define __IE_DLL_EXPORTS__
#include "IEphysicPolygon.h"

IE_BEGIN

IEPhysicPolygon::IEPhysicPolygon()
{

}

IEPhysicPolygon::~IEPhysicPolygon()
{

}

void IEPhysicPolygon::Initialization(IEPhysicEdgeInfo * physicEdgeInfo)
{
	m_physicEdgeInfo = physicEdgeInfo;
}

IEPhysicPolygon * IEPhysicPolygon::Create(IEPhysicEdgeInfo * physicEdgeInfo)
{
	IEPhysicPolygon * physicEdge = new IEPhysicPolygon();
	physicEdge->Initialization(physicEdgeInfo);
	return physicEdge;
}

void IEPhysicPolygon::DrawPhysicEdge()
{
	IEVector * vertexs = ((IEPhysicPolygonInfo *)m_physicEdgeInfo)->m_vertexs;
	int vertexsCount = ((IEPhysicPolygonInfo *)m_physicEdgeInfo)->m_vertexsCount;

	glBegin(GL_TRIANGLE_FAN);
	for (int index = 0; index < vertexsCount; index++)
	{
		glVertex2f(vertexs[index].m_x, vertexs[index].m_y);
	}
	glEnd();
}

IEVector IEPhysicPolygon::GetBarycenter()
{
	IEVector * vertexs = ((IEPhysicPolygonInfo *)m_physicEdgeInfo)->m_vertexs;
	int vertexsCount = ((IEPhysicPolygonInfo *)m_physicEdgeInfo)->m_vertexsCount;
	IEVector center = IEVector(0.0f, 0.0f);

	for (int index = 0; index < vertexsCount; index++)
	{
		center = center + vertexs[index];
	}
	center = center / vertexsCount;
	return center;
}

IE_END