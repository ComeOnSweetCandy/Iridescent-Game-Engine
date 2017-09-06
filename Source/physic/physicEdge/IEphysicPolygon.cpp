#define __IE_DLL_EXPORTS__
#include "IEphysicPolygon.h"

#include "../../type/IEstring.h"
#include "../../core/container/IEcontianer.h"

IE_BEGIN

IEPhysicPolygon::IEPhysicPolygon()
{
	m_edgeType = __edge_polygon__;
}

IEPhysicPolygon::~IEPhysicPolygon()
{
	delete[]m_vertexs;
}

void IEPhysicPolygon::Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString  * infos)
{
	IEPhysicEdge::Initialization(edgeType, barycenterX, barycenterY);
	
	IEPhysicPolygon::SetVertexs(infos);
}

IEPhysicPolygon * IEPhysicPolygon::Create(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos)
{
	IEPhysicPolygon * physicEdge = new IEPhysicPolygon();
	physicEdge->Initialization(edgeType, barycenterX, barycenterY, infos);
	return physicEdge;
}

void IEPhysicPolygon::DrawPhysicEdge()
{
	glBegin(GL_TRIANGLE_FAN);
	for (unsigned int index = 0; index < m_vertexsNum; index++)
	{
		glVertex2f(m_vertexs[index][0], m_vertexs[index][1]);
	}
	glEnd();
}

void IEPhysicPolygon::SetVertexs(IEString * infos)
{
	IEContainer * container = infos->SplitBy(',');
	IEString ** arrays = (IEString **)(container->GetContainer());
	m_vertexsNum = container->Count() / 2;
	m_vertexs = new IEVector[m_vertexsNum];

	for (unsigned int index = 0; index < m_vertexsNum; index++)
	{
		m_vertexs[index].m_x = arrays[index * 2]->transToFloat();
		m_vertexs[index].m_y = arrays[index * 2 + 1]->transToFloat();
	}
}

IE_END