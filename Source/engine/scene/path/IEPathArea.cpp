#define __IE_DLL_EXPORTS__
#include "IEPathArea.h"

#include "../../../physic/physicEdge/IEphysicPolygon.h"
#include "../../../physic/IEphysicEdgeCollision.h"
#include "../../../type/IEbaseType.h"

IE_BEGIN

IEPathArea::IEPathArea()
{

}

IEPathArea::~IEPathArea()
{

}

void IEPathArea::Initialization(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEArea::Initialization(map, halfViewBlocks, blockSize);
}

IEPathArea * IEPathArea::Create(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEPathArea * path = new IEPathArea();
	path->Initialization(map, halfViewBlocks, blockSize);
	return path;
}

void IEPathArea::Visit()
{

}

IEChunk * IEPathArea::CreateChunk()
{
	return IEPathChunk::Create(m_chunkLength);
}

void IEPathArea::SetTunnel(int * datas, unsigned char tunnel)
{
	//先进行转换
	int chunkLocationX, chunkLocationY, explictLocationX, explictLocationY;
	LocationTranslate(datas[0], datas[1], chunkLocationX, chunkLocationY, explictLocationX, explictLocationY);

	//获取chunk
	IEPathChunk * chunk = (IEPathChunk *)(GetChunk(chunkLocationX, chunkLocationY));

	//获取tunnels
	unsigned char *** _tunnels = chunk->m_tunnels;
	int index = datas[2] * PATH_PRECISION + datas[3];
	_tunnels[explictLocationX][explictLocationY][index] = _tunnels[explictLocationX][explictLocationY][index] & tunnel;
}

void IEPathArea::ReckonAddPath(IEPhysicNode * physicNode)
{	
	if (!physicNode)
	{
		return;
	}

	//记录下所有已经检测过的点
	m_list = IEArray::CreateAndRetain();

	//计算重心点
	IEVector barycenter = physicNode->GetBarycenter();
	IEGrid gridGrid = IEGrid(barycenter);
	IEGrid tunnelGrid = IEGrid((barycenter - gridGrid) / (1.0f / PATH_PRECISION));
	
	//计算该点是否在physicNode的物理范围内 需要一个标记值
	ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid);

	int index = 0;
	while (IEBaseType<int[5]> * param = (IEBaseType<int[5]> *)(m_list->Find(index++)))
	{
		int * data = param->GetData();

		gridGrid = IEGrid(data[0], data[1]);
		tunnelGrid = IEGrid(data[2], data[3]);

		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(1, 0));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(-1, 0));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(0, 1));
		ReckonPhysicNodeDot(physicNode, gridGrid, tunnelGrid + IEGrid(0, -1));
	}
	
	//最后计算这些点的通道变化
	int count = m_list->Count();
	IEBaseType<int[5]> ** i = (IEBaseType<int[5]> **)(m_list->GetContainer());
	for (int index = 0; index < count; index++)
	{
		int * data = ((IEBaseType<int[5]> *)(m_list->Find(index)))->GetData();
		IEPath * path = (IEPath *)GetBlock(data[0], data[1]);
		//path->SetTunnel(curTunnelGrid.m_x, curTunnelGrid.m_y, 0);
		
		if (data[4] == 0)
		{
			//点在物理范围外，即物理体的边缘位置 需要检测周围8个点 是否在列表内


		}
		else if (data[4] == 1)
		{
			SetTunnel(data, 0);
			//说明整个点都在物理范围内 直接通道全部关闭
			//path->SetTunnel(data[2], data[3], 0);
		}
	}

	m_list->Release();
}

void IEPathArea::ReckonDelPath(IEPhysicNode * physicNode)
{

}

void IEPathArea::ReckonPhysicNodeDot(IEPhysicNode * physicNode, IEGrid curGrid, IEGrid curTunnelGrid)
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

	//首先检测这个点是否已经在列表中存在了
	int count = m_list->Count();
	IEBaseType<int[5]> ** i = (IEBaseType<int[5]> **)(m_list->GetContainer());
	for (int index = 0; index < count; index++)
	{
		int * data = ((IEBaseType<int[5]> *)(m_list->Find(index)))->GetData();
		if (curGrid.m_x == data[0] && curGrid.m_y == data[1] && curTunnelGrid.m_x == data[2] && curTunnelGrid.m_y == data[3])
		{
			return;
		}
	}

	//判断点是否在physicNode的物理范围内
	IEVector worldPosition = curGrid + curTunnelGrid * (1.0f / PATH_PRECISION);
	bool res = ReckonDotInPhysicNode(physicNode, worldPosition);

	//将点放入列表 标记好是否在物理范围内
	IEBaseType<int[5]> * param = IEBaseType<int[5]>::Create();
	m_list->Push(param);

	int * data = param->GetData();
	data[0] = curGrid.m_x;
	data[1] = curGrid.m_y;
	data[2] = curTunnelGrid.m_x;
	data[3] = curTunnelGrid.m_y;
	data[4] = res ? 1 : 0;
}

bool IEPathArea::ReckonDotInPhysicNode(IEPhysicNode * physicNode, IEVector position)
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