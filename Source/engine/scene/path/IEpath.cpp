#define __IE_DLL_EXPORTS__
#include "IEpath.h"

#include "../../../physic/physicEdge/IEphysicPolygon.h"
#include "../../../physic/IEphysicEdgeCollision.h"
#include "../../../type/IEbaseType.h"

IE_BEGIN

IEPath::IEPath()
{

}

IEPath::~IEPath()
{

}

void IEPath::Initialization(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEArea::Initialization(map, halfViewBlocks, blockSize);
}

IEPath * IEPath::Create(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEPath * path = new IEPath();
	path->Initialization(map, halfViewBlocks, blockSize);
	return path;
}

void IEPath::Visit()
{

}

IEChunk * IEPath::CreateChunk()
{
	return IEPathBlock::Create(m_chunkLength);
}

void IEPath::ReckonPath(IEPhysicNode * physicNode)
{	
	if (!physicNode)
	{
		return;
	}

	m_list = IEArray::CreateAndRetain();

	IEVector barycenter = physicNode->GetBarycenter();
	IEGrid gridGrid = IEGrid(barycenter);
	IEGrid tunnelGrid = IEGrid((barycenter - gridGrid) / (1.0f / PATH_PRECISION));
	
	ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid);

	int index = 0;
	while (IEBaseType<int[4]> * param = (IEBaseType<int[4]> *)(m_list->Find(index++)))
	{
		int * data = param->GetData();

		gridGrid = IEGrid(data[0], data[1]);
		tunnelGrid = IEGrid(data[2], data[3]);

		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(1, 0));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(-1, 0));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(0, 1));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(0, -1));
	}

	m_list->Release();
}

void IEPath::RecoverPhysicNodeRange(IEPhysicNode * phsyicNode)
{
	//回退物理占据的空间
}

void IEPath::ReckonPhysicNodeDot(IEPhysicNode * physicNode, IEGrid curGrid, IEGrid curTunnelGrid)
{
	if (curTunnelGrid.m_x >= PATH_PRECISION)
	{
		curGrid = curGrid + IEVector(1, 0);
		curTunnelGrid.m_x = 0;
	}
	else if (curTunnelGrid.m_x < 0)
	{
		curGrid = curGrid + IEVector(-1, 0);
		curTunnelGrid.m_x = 3;
	}
	else if (curTunnelGrid.m_y >= PATH_PRECISION)
	{
		curGrid = curGrid + IEVector(0, 1);
		curTunnelGrid.m_y = 0;
	}
	else if (curTunnelGrid.m_y < 0)
	{
		curGrid = curGrid + IEVector(0, -1);
		curTunnelGrid.m_y = 3;
	}

	int count = m_list->Count();
	IEBaseType<int[4]> ** i = (IEBaseType<int[4]> **)(m_list->GetContainer());
	for (int index = 0; index < count; index++)
	{
		int * data = ((IEBaseType<int[4]> *)(m_list->Find(index)))->GetData();
		if (curGrid.m_x == data[0] && curGrid.m_y == data[1] && curTunnelGrid.m_x == data[2] && curTunnelGrid.m_y == data[3])
		{
			return;
		}
	}

	IEVector worldPosition = curGrid + curTunnelGrid * (1.0f / PATH_PRECISION);
	bool res = ReckonDotInPhysicNode(physicNode, worldPosition);

	if (res)
	{
		IEBaseType<int[4]> * param = IEBaseType<int[4]>::Create();
		int * data = param->GetData();
		data[0] = curGrid.m_x;
		data[1] = curGrid.m_y;
		data[2] = curTunnelGrid.m_x;
		data[3] = curTunnelGrid.m_y;
		m_list->Push(param);

		IEPathGrid * pathGrid = (IEPathGrid *)GetBlock(curGrid.m_x, curGrid.m_y);
		pathGrid->SetTunnel(curTunnelGrid.m_x, curTunnelGrid.m_y, 0);
	}
	else
	{
		return;
	}
}

bool IEPath::ReckonDotInPhysicNode(IEPhysicNode * physicNode, IEVector position)
{
	IEPhysicPolygon * polygon = (IEPhysicPolygon *)(physicNode->GetPhysicEdge());
	IEPhysicPolygonInfo * polygonInfo = (IEPhysicPolygonInfo *)(polygon->GetPhysicEdgeInfo());

	IEVector bPosition = position;
	IEVector aPosition = physicNode->GetPhysicPosition();

	IEVector N = IEVector(0.0f, 0.0f);
	float t = 1.0f;
	IEPhysicEdgeCollision::PD_Collide(polygonInfo->m_vertexs, polygonInfo->m_vertexsCount, bPosition - aPosition, IEVector(0.0f, 0.0f), N, t);
	if (t <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IE_END