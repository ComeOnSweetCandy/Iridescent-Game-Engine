#define __IE_DLL_EXPORTS__
#include "IEmarble.h"

IE_BEGIN

IEMarble::IEMarble()
{
	m_map = NULL;
	m_marbleAlter = NULL;
	m_marbleAlters = NULL;
}

IEMarble::~IEMarble()
{
	__IE_RELEASE__(m_marbleAlters);
}

void IEMarble::Initialization(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEArea::Initialization(map, halfViewBlocks, blockSize);

	m_marbleAlters = IEContainer::CreateAndRetain();
}

IEMarble * IEMarble::Create(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEMarble * terrain = new IEMarble();
	terrain->Initialization(map, halfViewBlocks, blockSize);
	return terrain;
}

IEChunk * IEMarble::CreateChunk()
{
	return IEMarbleBlock::Create(m_sideLength);
}

void IEMarble::LoadChunk(int blockX, int blockY)
{
	m_map->LoadMarbleChunk(blockX, blockY);
}

void IEMarble::LoadChild(int blockX, int blockY, IEMarbleAlterInfo * alterInfos)
{

}

void IEMarble::AddChild(unsigned int marbleID, int gridX, int gridY)
{
	m_marbleAlter = new IEMarbleAlterCache();
	m_marbleAlter->_X = gridX;
	m_marbleAlter->_Y = gridY;
	m_marbleAlter->_MarbleInfo._MarbleID = marbleID;
	m_marbleAlters->Push(m_marbleAlter);

	ApplyBody(marbleID, gridX, gridY);
}

void IEMarble::ApplyBody(unsigned int marbleID, int gridX, int gridY)
{
	IEMarbleInfo * infos = IEMarblesInfoManager::Share()->GetMarblesInfoList();
	IEString textureGroupName = IEString(infos[marbleID]._MarbleName);
	int randIndex;

	//主体部分
	if (infos[marbleID]._BodyC)
	{
		randIndex = rand() % infos[marbleID]._BodyC;
		IEMarbleGrid * grid = (IEMarbleGrid *)GetBlock(gridX, gridY);
		if (grid != NULL)
		{
			m_marbleAlter->_MarbleInfoOld._MarbleID = grid->GetMarbleID();

			RemoveChild(gridX, gridY);
		}
		


		grid = IEMarbleGrid::Create(marbleID);
		grid->ChangeTexture((textureGroupName + "/body_" + randIndex + ".png").GetString());
		IEArea::AddChild(grid, gridX, gridY);

		

		IEGrid size = grid->GetMarbleSize();
		for (int x = 0; x < size.m_x; x++)
		{
			for (int y = 0; y < size.m_y; y++)
			{
				StanceChild(grid, gridX + x, gridY + y);
			}
		}

		

		if (infos[marbleID]._BorderC)
		{
			ApplyBorder(grid, marbleID, gridX, gridY);
		}

		

		if (infos[marbleID]._BorderC)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					IEMarbleGrid * aroundGrid = (IEMarbleGrid *)GetBlock(gridX + x, gridY + y);
					if (aroundGrid)
					{
						ApplyCorner(aroundGrid, marbleID, gridX + x, gridY + y);
					}
				}
			}
		}
	}
}

void IEMarble::ApplyBorder(IEMarbleGrid * grid, unsigned int marbleID, int gridX, int gridY)
{
	IEMarbleInfo * infos = IEMarblesInfoManager::Share()->GetMarblesInfoList();
	IEString textureGroupName = IEString(infos[marbleID]._MarbleName);


	IEMarbleGrid * grids[4];
	grids[0] = (IEMarbleGrid *)GetBlock(gridX, gridY - 1);
	grids[1] = (IEMarbleGrid *)GetBlock(gridX + 1, gridY);
	grids[2] = (IEMarbleGrid *)GetBlock(gridX, gridY + 1);
	grids[3] = (IEMarbleGrid *)GetBlock(gridX - 1, gridY);

	for (int index = 0; index < 4; index++)
	{
		if (grids[index] == NULL)
		{
			grid->SetDisplayBorder(index, true);
		}
		else
		{
			if (grids[index]->ValidateMarbleID(marbleID))
			{
				grid->SetDisplayBorder(index, false);
				grids[index]->SetDisplayBorder((index + 2) % 4, false);

				//计算自身的内角
				grids[index]->AnalyseCorner();
			}
			else
			{
				grid->SetDisplayBorder(index, true);
			}
		}
	}

	//是否有边需要生成
	if (infos[marbleID]._BorderC)
	{
		int randIndex = rand() % infos[marbleID]._BorderC;

		bool * border = grid->GetDisplayBorder();
		if (border[0] || border[1] || border[2] || border[3])
		{
			grid->SetBorderTexture((textureGroupName + "/border_" + randIndex + ".png").GetString());
		}
		else
		{
			grid->SetBorderTexture(NULL);
		}
	}


	//计算自身的内角
	grid->AnalyseCorner();

	//是否有角需要生成
	if (infos[marbleID]._CornerC)
	{
		bool * corner = grid->GetDisplayCorner();
		if (corner[0] || corner[1] || corner[2] || corner[3])
		{
			int randIndex = rand() % infos[marbleID]._CornerC;

			grid->SetCornerSprite((textureGroupName + "/corner_" + randIndex + ".png").GetString());
		}
		else
		{
			grid->SetCornerSprite(NULL);
		}
	}
}

void IEMarble::ApplyCorner(IEMarbleGrid * grid, unsigned int marbleID, int gridX, int gridY)
{
	IEMarbleInfo * infos = IEMarblesInfoManager::Share()->GetMarblesInfoList();
	IEString textureGroupName = IEString(infos[marbleID]._MarbleName);

	if (!infos[marbleID]._CornerC)
	{
		return;
	}

	int randIndex = rand() % infos[marbleID]._CornerC;

	bool * border = grid->GetDisplayBorder();

	//得到四个斜边元素
	IEMarbleGrid * grids[4];
	grids[0] = (IEMarbleGrid *)GetBlock(gridX + 1, gridY - 1);
	grids[1] = (IEMarbleGrid *)GetBlock(gridX + 1, gridY + 1);
	grids[2] = (IEMarbleGrid *)GetBlock(gridX - 1, gridY + 1);
	grids[3] = (IEMarbleGrid *)GetBlock(gridX - 1, gridY - 1);

	//计算外角
	for (int index = 0; index < 4; index++)
	{
		int x = index;
		int y = (index + 1) % 4;
		if (!border[x] && !border[y])	//说明两边都没有边框
		{
			if (grids[index])	//如果斜边角有grid
			{
				if (grids[index]->ValidateMarbleID(marbleID))	//如果是一样的marble
				{
					grid->SetDisplayTurner(index, false);
				}
				else
				{
					grid->SetDisplayTurner(index, true);
				}
			}
			else
			{
				grid->SetDisplayTurner(index, true);
			}
		}
	}

	bool * turner = grid->GetDisplayTurner();
	if (turner[0] || turner[1] || turner[2] || turner[3])
	{
		grid->SetTurnerSprite((textureGroupName + "/turner_" + randIndex + ".png").GetString());
	}
	else
	{
		grid->SetTurnerSprite(NULL);
	}
}

void IEMarble::RemoveChild(int gridX, int gridY)
{
	//IETerrainGrid * grid = (IETerrainGrid *)GetGrid(gridX, gridY);
	//if (grid != NULL)
	//{
	//	RemoveChild(gridX, gridY);

	//	IETerrainGrid * grids[4];
	//	grids[0] = (IETerrainGrid *)GetGrid(gridX, gridY - 1);
	//	grids[1] = (IETerrainGrid *)GetGrid(gridX + 1, gridY);
	//	grids[2] = (IETerrainGrid *)GetGrid(gridX, gridY + 1);
	//	grids[3] = (IETerrainGrid *)GetGrid(gridX - 1, gridY);
	//	for (int index = 0; index < 4; index++)
	//	{
	//		if (grids[index] != NULL && grids[index]->ValidateTerrainGridMode(__terrain_body_mode__))
	//		{
	//			grids[index]->SetDisplayTerrainBorder((index + 2) % 4, true);
	//		}
	//	}
	//}
}

void IEMarble::RollbackAlter()
{

}

void IEMarble::RollbackAlters()
{
	IEObject * object = m_marbleAlters->PopTop();
	m_marbleAlter = (IEMarbleAlterCache *)object;
}

IE_END