#define __IE_DLL_EXPORTS__
#include "IEpathFinder.h"

#include "../engine/scene/IEmap.h"
#include "../engine/scene/path/IEpath.h"
#include "../physic/physicEdge/IEphysicCircle.h"
#include "../type/IEbaseType.h"

IE_BEGIN

IEPathFinder::IEPathFinder()
{
	m_activeList = NULL;
	m_closeList = NULL;
	m_list = NULL;
}

IEPathFinder::~IEPathFinder()
{
	m_activeList = NULL;
	m_closeList = NULL;
	m_list = NULL;
}

void IEPathFinder::Initialization(IEPath * path)
{
	SetPath(path);
}

IEPathFinder * IEPathFinder::Create(IEPath * path)
{
	IEPathFinder * pathFinder = new IEPathFinder();
	pathFinder->Initialization(path);
	return pathFinder;
}

void IEPathFinder::SetPath(IEPath * path)
{
	m_path = path;
}

IEArray * IEPathFinder::FindPath(IEPhysicNode * physicNode, IEVector staPosition, IEVector endPosition)
{
	IEGrid staGrid;
	IEGrid endGrid;
	IEGrid staTunnel;
	IEGrid endTunnel;
	m_roadPhysicNode = physicNode;
	HandleGrid(staPosition, endPosition, staGrid, staTunnel, endGrid, endTunnel);

	return FindPaths(staGrid, staTunnel, endGrid, endTunnel);
}

void IEPathFinder::HandleGrid(IEVector staPosition, IEVector endPosition, IEGrid &staGrid, IEGrid &staTunnel, IEGrid &endGrid, IEGrid &endTunnel)
{
	staPosition.m_x < 0.0f ? staGrid.m_x = staPosition.m_x - 1 : staGrid.m_x = staPosition.m_x;
	staPosition.m_y < 0.0f ? staGrid.m_y = staPosition.m_y - 1 : staGrid.m_y = staPosition.m_y;
	endPosition.m_x < 0.0f ? endGrid.m_x = endPosition.m_x - 1 : endGrid.m_x = endPosition.m_x;
	endPosition.m_y < 0.0f ? endGrid.m_y = endPosition.m_y - 1 : endGrid.m_y = endPosition.m_y;

	staTunnel = (staPosition - staGrid) / 0.25f;
	endTunnel = (endPosition - endGrid) / 0.25f;

	staGrid = staGrid + staTunnel / 4;
	endGrid = endGrid + endTunnel / 4;

	staTunnel = staTunnel % 4;
	endTunnel = endTunnel % 4;
}

IEArray * IEPathFinder::FindPaths(IEGrid staGrid, IEGrid staTunnel, IEGrid endGrid, IEGrid endTunnel)
{
	m_activeList = IEArray::CreateAndRetain();
	m_closeList = IEArray::CreateAndRetain();

	IEGrid curGrid = staGrid;
	IEGrid curTunnel = staTunnel;

	IEPathNode * curPathNode = new IEPathNode();
	curPathNode->m_grid = curGrid;
	curPathNode->m_tunnel = curTunnel;
	curPathNode->m_parentPathNode = curPathNode;
	curPathNode->m_pass = 0;
	curPathNode->m_last = EstimateStraightDistance(curGrid, curTunnel, endGrid, endTunnel);
	curPathNode->m_estimate = curPathNode->m_last + curPathNode->m_pass;
	m_activeList->Push(curPathNode);

	while (curPathNode->m_grid != endGrid || curPathNode->m_tunnel != endTunnel)
	{
		//这里进行调整，首先选取的方向 应当为 朝向的方向
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x == y || x == -y)
				{
					//not support slant
					continue;
				}

				IEGrid surroundGrid = curPathNode->m_grid;
				IEGrid surroundTunnel = curPathNode->m_tunnel + IEGrid(x, y);
				if (surroundTunnel.m_x < 0)
				{
					surroundTunnel.m_x = PATH_PRECISION - 1;
					surroundGrid = surroundGrid - IEGrid(1, 0);
				}
				if (surroundTunnel.m_x >= PATH_PRECISION)
				{
					surroundTunnel.m_x = 0;
					surroundGrid = surroundGrid + IEGrid(1, 0);
				}
				if (surroundTunnel.m_y < 0)
				{
					surroundTunnel.m_y = PATH_PRECISION - 1;
					surroundGrid = surroundGrid - IEGrid(0, 1);
				}
				if (surroundTunnel.m_y >= PATH_PRECISION)
				{
					surroundTunnel.m_y = 0;
					surroundGrid = surroundGrid + IEGrid(0, 1);
				}

				IEPathGrid * pathGrid = (IEPathGrid *)(m_path->GetBlock(surroundGrid.m_x, surroundGrid.m_y));
				unsigned char tunnelPassed = pathGrid->GetGridTunnelPassed(surroundTunnel.m_x, surroundTunnel.m_y);

				if (tunnelPassed == 0)
				{
					//如果本身没有路径
					continue;
				}

				if (FindNodeInCloseList(surroundGrid, surroundTunnel))
				{
					//该路径节点 已经进入了关闭列表
					continue;
				}

				if (CheckVolumn(surroundGrid, surroundTunnel))
				{
					//该路径节点 体积与周边相交
					continue;
				}

				int pass = curPathNode->m_pass + 1;
				IEPathNode * surroundNode = FindNodeInActiveList(surroundGrid, surroundTunnel);

				if (surroundNode)
				{
					if (pass < surroundNode->m_pass)
					{
						surroundNode->m_pass = pass;
						surroundNode->m_estimate = surroundNode->m_last + surroundNode->m_pass;
						surroundNode->m_parentPathNode = curPathNode;
					}
				}
				else
				{
					IEPathNode * pathNode = new IEPathNode();
					pathNode->m_grid = surroundGrid;
					pathNode->m_tunnel = surroundTunnel;
					pathNode->m_parentPathNode = curPathNode;
					pathNode->m_pass = pass;
					pathNode->m_last = EstimateStraightDistance(surroundGrid, surroundTunnel, endGrid, endTunnel);
					pathNode->m_estimate = pathNode->m_last + pathNode->m_pass;
					m_activeList->Push(pathNode);
				}
			}
		}

		m_activeList->Pop(curPathNode);
		m_activeList->AddCount(1);
		m_closeList->Push(curPathNode);

		IEPathNode ** nodes = (IEPathNode **)(m_activeList->GetContainer());
		unsigned nodeCount = m_activeList->Count();
		if (nodeCount != 0)
		{
			curPathNode = nodes[0];
			for (unsigned int index = 0; index < nodeCount; index++)
			{
				if (!curPathNode)
				{
					curPathNode = nodes[index];
				}
				else
				{
					if (IEPathNode * pathNode = nodes[index])
					{
						if (curPathNode->m_estimate > pathNode->m_estimate)
						{
							curPathNode = pathNode;
						}
					}
				}
			}
		}
		else
		{
			break;
			//没有找到路径 直接返回了
		}
	}

	IEArray * steps = IEArray::CreateAndRetain();
	while (curPathNode->m_grid != staGrid || curPathNode->m_tunnel != staTunnel)
	{
		IEVector * stepPosition = new IEVector(curPathNode->m_grid + curPathNode->m_tunnel * (1.0f / PATH_PRECISION));
		steps->Push(stepPosition);

		//printf("%d  %d  %d   %d    %f   %f\n", curPathNode->m_grid.m_x, curPathNode->m_grid.m_y, curPathNode->m_tunnel.m_x, curPathNode->m_tunnel.m_y, stepPosition->m_x, stepPosition->m_y);

		curPathNode = curPathNode->m_parentPathNode;
	}
	IEVector * stepPosition = new IEVector(curPathNode->m_grid + curPathNode->m_tunnel * (1.0f / PATH_PRECISION));
	steps->Push(stepPosition);
	//printf("%d  %d  %d   %d    %f   %f\n", curPathNode->m_grid.m_x, curPathNode->m_grid.m_y, curPathNode->m_tunnel.m_x, curPathNode->m_tunnel.m_y, stepPosition->m_x, stepPosition->m_y);

	__IE_RELEASE__(m_activeList);
	__IE_RELEASE__(m_closeList);

	for (int i = steps->Count()-1; i >=0 ; i--)
	{
		IEVector * v = ((IEVector *)(steps->Find(i)));
		printf("%f   %f\n", v->m_x, v->m_y);
	}

	return steps;
}

int IEPathFinder::EstimateStraightDistance(IEGrid curGrid, IEGrid curTunnel, IEGrid endGrid, IEGrid endTunnel)
{
	IEGrid gridOffset = (endGrid - curGrid) * PATH_PRECISION;
	IEGrid tunnelOffset = endTunnel - curTunnel;
	IEGrid distance = (gridOffset + tunnelOffset).Absolute();

	return distance.m_x + distance.m_y;
}

IEPathNode * IEPathFinder::FindNodeInActiveList(IEGrid grid, IEGrid tunnel)
{
	IEObject ** nodes = m_activeList->GetContainer();
	unsigned nodeCount = m_activeList->Count();
	for (unsigned int index = 0; index < nodeCount; index++)
	{
		IEPathNode * node = (IEPathNode *)nodes[index];
		if (node && node->m_grid == grid && node->m_tunnel == tunnel)
		{
			return node;
		}
	}
	return NULL;
}

IEPathNode * IEPathFinder::FindNodeInCloseList(IEGrid grid, IEGrid tunnel)
{
	IEObject ** nodes = m_closeList->GetContainer();
	unsigned nodeCount = m_closeList->Count();
	for (unsigned int index = 0; index < nodeCount; index++)
	{
		IEPathNode * node = (IEPathNode *)nodes[index];
		if (node->m_grid == grid && node->m_tunnel == tunnel)
		{
			return node;
		}
	}
	return NULL;
}

bool IEPathFinder::CheckVolumn(IEGrid curGrid, IEGrid curTunnel)
{
	m_list = IEArray::CreateAndRetain();

	IEPhysicCircleInfo * circleInfo = (IEPhysicCircleInfo *)(m_roadPhysicNode->GetPhysicEdge()->GetPhysicEdgeInfo());
	float circleRadius = circleInfo->m_radius;
	IEVector center = curGrid + curTunnel * (1.0f / PATH_PRECISION);
	
	IEBaseType<int[4]> * param = new IEBaseType<int[4]>();
	(param->GetData())[0] = curGrid.m_x;
	(param->GetData())[1] = curGrid.m_y;
	(param->GetData())[2] = curTunnel.m_x;
	(param->GetData())[3] = curTunnel.m_y;
	m_list->Push(param);
	
	int index = 0;
	while (param = (IEBaseType<int[4]> *)(m_list->Find(index)))
	{
		int * data = param->GetData();
		bool res1 = InVolumn(circleRadius, center, IEGrid(data[0], data[1]), IEGrid(data[2] + 1, data[3]));
		bool res2 = InVolumn(circleRadius, center, IEGrid(data[0], data[1]), IEGrid(data[2] - 1, data[3]));
		bool res3 = InVolumn(circleRadius, center, IEGrid(data[0], data[1]), IEGrid(data[2], data[3] + 1));
		bool res4 = InVolumn(circleRadius, center, IEGrid(data[0], data[1]), IEGrid(data[2], data[3] - 1));
		index++;

		if (res1 || res2 || res3 || res4)
		{
			__IE_RELEASE__(m_list);
			return true;
		}
	}

	__IE_RELEASE__(m_list);
	return false;
}

bool IEPathFinder::InVolumn(float radius, IEVector center, IEGrid grid, IEGrid tunnel)
{
	if (tunnel.m_x < 0)
	{
		tunnel.m_x = PATH_PRECISION - 1;
		grid = grid - IEGrid(1, 0);
	}
	if (tunnel.m_x >= PATH_PRECISION)
	{
		tunnel.m_x = 0;
		grid = grid + IEGrid(1, 0);
	}
	if (tunnel.m_y < 0)
	{
		tunnel.m_y = PATH_PRECISION - 1;
		grid = grid - IEGrid(0, 1);
	}
	if (tunnel.m_y >= PATH_PRECISION)
	{
		tunnel.m_y = 0;
		grid = grid + IEGrid(0, 1);
	}

	//如果已经检测过了，就不需要再次进行检测
	for (int index = 0; index < m_list->Count(); index++)
	{
		IEBaseType<int[4]> * param = (IEBaseType<int[4]> *)(m_list->Find(index));
		int * data = param->GetData();

		if (data[0] == grid.m_x && data[1] == grid.m_y && data[2] == tunnel.m_x && data[3] == tunnel.m_y)
		{
			return false;
		}
	}

	IEVector position = grid + tunnel * (1.0f / PATH_PRECISION);
	IEVector interval = position - center;
	if (interval.Length() < radius)
	{
		//如果在范围之内		
		IEPathGrid * pathGrid = (IEPathGrid *)(m_path->GetBlock(grid.m_x, grid.m_y));

		unsigned char res = pathGrid->GetGridTunnelPassed(tunnel.m_x, tunnel.m_y);
		if (res == 0)
		{
			//通行为零
			return true;
		}

		IEBaseType<int[4]> * param = new IEBaseType<int[4]>();
		(param->GetData())[0] = grid.m_x;
		(param->GetData())[1] = grid.m_y;
		(param->GetData())[2] = tunnel.m_x;
		(param->GetData())[3] = tunnel.m_y;
		m_list->Push(param);
	}

	return false;
}

IE_END