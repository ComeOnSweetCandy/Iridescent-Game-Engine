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
	//�Ƚ���ת��
	int chunkLocationX, chunkLocationY, explictLocationX, explictLocationY;
	LocationTranslate(datas[0], datas[1], chunkLocationX, chunkLocationY, explictLocationX, explictLocationY);

	//��ȡchunk
	IEPathChunk * chunk = (IEPathChunk *)(GetChunk(chunkLocationX, chunkLocationY));

	//��ȡtunnels
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

	//��¼�������Ѿ������ĵ�
	m_list = IEArray::CreateAndRetain();

	//�������ĵ�
	IEVector barycenter = physicNode->GetBarycenter();
	IEGrid gridGrid = IEGrid(barycenter);
	IEGrid tunnelGrid = IEGrid((barycenter - gridGrid) / (1.0f / PATH_PRECISION));
	
	//����õ��Ƿ���physicNode������Χ�� ��Ҫһ�����ֵ
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
	
	//��������Щ���ͨ���仯
	int count = m_list->Count();
	IEBaseType<int[5]> ** i = (IEBaseType<int[5]> **)(m_list->GetContainer());
	for (int index = 0; index < count; index++)
	{
		int * data = ((IEBaseType<int[5]> *)(m_list->Find(index)))->GetData();
		IEPath * path = (IEPath *)GetBlock(data[0], data[1]);
		//path->SetTunnel(curTunnelGrid.m_x, curTunnelGrid.m_y, 0);
		
		if (data[4] == 0)
		{
			//��������Χ�⣬��������ı�Եλ�� ��Ҫ�����Χ8���� �Ƿ����б���


		}
		else if (data[4] == 1)
		{
			SetTunnel(data, 0);
			//˵�������㶼������Χ�� ֱ��ͨ��ȫ���ر�
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

	//���ȼ��������Ƿ��Ѿ����б��д�����
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

	//�жϵ��Ƿ���physicNode������Χ��
	IEVector worldPosition = curGrid + curTunnelGrid * (1.0f / PATH_PRECISION);
	bool res = ReckonDotInPhysicNode(physicNode, worldPosition);

	//��������б� ��Ǻ��Ƿ�������Χ��
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