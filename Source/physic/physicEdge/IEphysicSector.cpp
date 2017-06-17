#define __IE_DLL_EXPORTS__
#include "IEphysicSector.h"

IE_BEGIN

IEPhysicSector::IEPhysicSector()
{

}

IEPhysicSector::~IEPhysicSector()
{

}

void IEPhysicSector::Initialization(IEPhysicEdgeInfo * physicEdgeInfo)
{
	m_physicEdgeInfo = physicEdgeInfo;
}

IEPhysicSector * IEPhysicSector::Create(IEPhysicEdgeInfo * physicEdgeInfo)
{
	IEPhysicSector * physicEdge = new IEPhysicSector();
	physicEdge->Initialization(physicEdgeInfo);
	return physicEdge;
}

void IEPhysicSector::DrawPhysicEdge()
{
	float radius = ((IEPhysicSectorInfo *)m_physicEdgeInfo)->m_radius;
	float angle = ((IEPhysicSectorInfo *)m_physicEdgeInfo)->m_angle;
	int vertexsCount = ((IEPhysicSectorInfo *)m_physicEdgeInfo)->m_vertexsCount;

	glBegin(GL_TRIANGLE_FAN);
	for (int index = -vertexsCount / 2; index <= vertexsCount/2; index++)
	{
		float tri = 2 * angle / vertexsCount * index;
		glVertex2f(cos(tri)*radius, sin(tri)*radius);
	}
	glEnd();
}

IEVector IEPhysicSector::GetBarycenter()
{ 
	return IEVector(0.0f, 0.0f); 
}

IE_END