#define __IE_DLL_EXPORTS__
#include "IEphysicCircle.h"

#include "../../type/IEstring.h"

IE_BEGIN

IEPhysicCircle::IEPhysicCircle()
{
	m_edgeType = __edge_circle__;
	m_vertexsNum = 32;
}

IEPhysicCircle::~IEPhysicCircle()
{

}

void IEPhysicCircle::Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos)
{
	IEPhysicEdge::Initialization(edgeType, barycenterX, barycenterY);

	IEPhysicCircle::SetRadius(infos);
}

IEPhysicCircle * IEPhysicCircle::Create(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos)
{
	IEPhysicCircle * object = new IEPhysicCircle();
	object->Initialization(edgeType, barycenterX, barycenterY, infos);
	return object;
}

void IEPhysicCircle::DrawPhysicEdge()
{
	glTranslatef(m_barycenter[0], m_barycenter[1], 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int index = 0; index < m_vertexsNum; index++)
	{
		float tri = 2 * IEPI / m_vertexsNum * index;
		glVertex2f(cos(tri)*m_radius, sin(tri)*m_radius);
	}
	glEnd();
}

void IEPhysicCircle::SetRadius(float radius)
{
	m_radius = radius;
}

float IEPhysicCircle::GetRadius()
{
	return m_radius;
}

void IEPhysicCircle::SetRadius(IEString * infos)
{
	//将信息转换为float值
	float radius = infos->transToFloat();
	SetRadius(radius);
}

IE_END