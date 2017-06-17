#define __IE_DLL_EXPORTS__
#include "IEphysicCircle.h"

IE_BEGIN

IEPhysicCircle::IEPhysicCircle()
{

}

IEPhysicCircle::~IEPhysicCircle()
{

}

void IEPhysicCircle::Initialization(IEPhysicEdgeInfo * physicEdgeInfo)
{
	IEPhysicEdge::Initialization(physicEdgeInfo);
}

IEPhysicCircle * IEPhysicCircle::Create(IEPhysicEdgeInfo * physicEdgeInfo)
{
	IEPhysicCircle * object = new IEPhysicCircle();
	object->Initialization(physicEdgeInfo);
	return object;
}

void IEPhysicCircle::DrawPhysicEdge()
{
	int vertexsCount = ((IEPhysicCircleInfo *)m_physicEdgeInfo)->m_vertexsCount;
	float radius = ((IEPhysicCircleInfo *)m_physicEdgeInfo)->m_radius;

	glBegin(GL_TRIANGLE_FAN);
	for (int index = 0; index < vertexsCount; index++)
	{
		float tri = 2 * IEPI / vertexsCount * index;
		glVertex2f(cos(tri)*radius, sin(tri)*radius);
	}
	glEnd();
}

void IEPhysicCircle::SetRadius(float radius)
{
	((IEPhysicCircleInfo *)m_physicEdgeInfo)->m_radius = radius;
}

float IEPhysicCircle::GetRadius()
{
	float radius = ((IEPhysicCircleInfo *)m_physicEdgeInfo)->m_radius;
	return radius;
}

IEVector IEPhysicCircle::GetBarycenter()
{
	return IEVector(0.0f, 0.0f);
}

IE_END