#define __IE_DLL_EXPORTS__
#include "IEphysicEdge.h"

IE_BEGIN

IEPhysicEdge::IEPhysicEdge()
{
	m_physicEdgeInfo = NULL;
}

IEPhysicEdge::~IEPhysicEdge()
{
	delete m_physicEdgeInfo;
}

void IEPhysicEdge::Initialization(IEPhysicEdgeInfo * physicEdgeInfo)
{
	m_physicEdgeInfo = physicEdgeInfo;
}

IEPhysicEdge * IEPhysicEdge::Create(IEPhysicEdgeInfo * physicEdgeInfo)
{
	__IE_WARNING__("IEPhysicEdgeInfo : error in function Create.\n");
	return NULL;
}

void IEPhysicEdge::SetPhysicEdgeInfo(IEPhysicEdgeInfo * physicEdgeInfo)
{
	m_physicEdgeInfo = physicEdgeInfo;
}

IEPhysicEdgeInfo * IEPhysicEdge::GetPhysicEdgeInfo()
{
	return m_physicEdgeInfo;
}

IEPhysicEdgeType IEPhysicEdge::GetEdgeType()
{ 
	return m_physicEdgeInfo->m_physicEdgeType; 
}

IE_END