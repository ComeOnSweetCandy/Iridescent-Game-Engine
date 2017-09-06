#define __IE_DLL_EXPORTS__
#include "IEphysicEdge.h"

IE_BEGIN

IEPhysicEdge::IEPhysicEdge()
{
	m_edgeType = __edge_typeCount__;
}

IEPhysicEdge::~IEPhysicEdge()
{
	
}

void IEPhysicEdge::Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY)
{
	edgeType = edgeType;
	m_barycenter.m_x = barycenterX;
	m_barycenter.m_y = barycenterY;
}

IEPhysicEdge * IEPhysicEdge::Create(IEEdgeType edgeType, float barycenterX, float barycenterY)
{
	__IE_WARNING__("IEPhysicEdgeInfo : error in function Create.\n");
	return NULL;
}

IEEdgeType IEPhysicEdge::GetEdgeType()
{
	return m_edgeType;
}

IEVector& IEPhysicEdge::GetBarycenter()
{
	return m_barycenter;
}

IE_END