#define __IE_DLL_EXPORTS__
#include "IETerrain.h"

IE_BEGIN

IETerrain::IETerrain()
{
	m_sceneType = __ie_scene_terrain__;
	m_map = NULL;
	m_alter = NULL;
	m_readyTerrainID = 0;
	m_readyTerrainMode = __terrain_none_mode__;

	strcpy(stringBody, "/body_");
	strcpy(stringBorder, "/border_");
	strcpy(stringNumber, "0"); 
	strcpy(stringPNG, ".png");
}

IETerrain::~IETerrain()
{

}

void IETerrain::Initialization(IEMap * map, int visibleRadius, int sideLength)
{
	IEArea::Initialization(map, visibleRadius, sideLength);

	m_terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
}

IETerrain * IETerrain::Create(IEMap * map, int visibleRadius, int sideLength)
{
	IETerrain * terrain = new IETerrain();
	terrain->Initialization(map, visibleRadius, sideLength);
	return terrain;
}

IEChunk * IETerrain::CreateChunk()
{
	return IETerrainChunk::Create(m_chunkLength);
}

void IETerrain::LoadChunk(int blockX, int blockY)
{
	m_map->LoadTerrainChunk(blockX, blockY);
}

void IETerrain::LoadChilds(IETerrainBlockFormat * blocks, int chunkLocationX, int chunkLocationY)
{
	IETerrainChunk * block = (IETerrainChunk *)GetChunk(chunkLocationX, chunkLocationY);
	block->ResetCache();

	m_loadString[0];
	m_loadString[1] = stringBody;
	m_loadString[2] = stringNumber;
	m_loadString[3] = stringPNG;
	
	unsigned int index = 0;
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			if (blocks)
			{
				if (blocks[index]._TerrainMode == __terrain_body_mode__)
				{
					LoadBody(block, x, y, blocks[index]._TerrainID, blocks[index]._Order);
				}
				else if (blocks[index]._TerrainMode == __terrain_none_mode__)
				{
					LoadNone(block, x, y, 0, 0);
				}

				index++;
			}
			else
			{
				LoadNone(block, x, y, 0, 0);
			}
		}
	}

	//在修改列表中 是否有当前block的更新
	//unsigned int count = m_alters->Count();
	//IETerrainAlter ** alters = (IETerrainAlter **)(m_alters->GetContainer());
	//for (index = 0; index < count; index++)
	//{
	//	if (alters[index]->_chunkLocationX == chunkLocationX && alters[index]->_chunkLocationY == chunkLocationY)
	//	{
	//		if (alters[index]->_TerrainInfo._TerrainMode == __terrain_body_mode__)
	//		{
	//			LoadBody(block, alters[index]->_explicitBlockLocationX, alters[index]->_explicitBlockLocationY, alters[index]->_TerrainInfo._TerrainID, alters[index]->_TerrainInfo._Order);
	//		}
	//		else if (alters[index]->_TerrainInfo._TerrainMode == __terrain_none_mode__)
	//		{
	//			LoadNone(block, alters[index]->_explicitBlockLocationX, alters[index]->_explicitBlockLocationY, 0, 0);
	//		}
	//	}
	//}

	//设置border sprite
	IEBlock *** gridArrays = block->GetBlocksMatrix();
	m_loadString[0];
	m_loadString[1] = stringBorder;
	m_loadString[2] = stringNumber;
	m_loadString[3] = stringPNG;
	
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IETerrainBlock * grid = (IETerrainBlock *)gridArrays[x][y];
			if (grid->IsDisplayBorder())
			{
				index = rand() % m_terrainsInfo[grid->GetTerrainID()]._BorderC;

				m_loadString[0] = m_terrainsInfo[grid->GetTerrainID()]._TerrainName;
				m_loadString[2][0] = '0' + index;

				RESOURCE.InsertKeyStrings(m_loadString, 4);
				IETexture * texture = (IETexture *)(RESOURCE.GetCufFind());

				if (texture)
				{
					grid->SetBorderTexture(texture);
				}
				else
				{
					char textureFile[64];

					sprintf(textureFile, "%s%s%d%s", m_terrainsInfo[grid->GetTerrainID()]._TerrainName, "/border_", index, ".png");
					grid->SetBorderTextureFile(textureFile);
				}
			}
		}
	}
}

void IETerrain::LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder)
{
	int randIndex;

	if (m_terrainsInfo[terrainID]._BodyC)
	{
		randIndex = rand() % m_terrainsInfo[terrainID]._BodyC;

		IETerrainBlock * grid = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY);
		grid->Reload(terrainID, __terrain_body_mode__, createdOrder); 

		m_loadString[0] = m_terrainsInfo[terrainID]._TerrainName;
		m_loadString[2][0] = '0' + randIndex;

		RESOURCE.InsertKeyStrings(m_loadString, 4);
		IETexture * texture = (IETexture *)(RESOURCE.GetCufFind());

		if (texture)
		{
			grid->ChangeTexture(texture);
		}
		else
		{
			char textureFile[64];

			sprintf(textureFile, "%s%s%d%s", m_terrainsInfo[terrainID]._TerrainName, "/body_", randIndex, ".png");
			grid->ChangeTexture(textureFile);
		}

		if (m_terrainsInfo[terrainID]._BorderC)
		{
			IETerrainBlock * grids[4];
			grids[0] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY - 1);
			grids[1] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX + 1, explicitGridPositionY);
			grids[2] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY + 1);
			grids[3] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX - 1, explicitGridPositionY);

			grid->AddNewCalBorder(grids);
		}
	}
}

void IETerrain::LoadNone(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder)
{
	IETerrainBlock * grid = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY);
	IETerrainBlock * grids[4];

	grids[0] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY - 1);
	grids[1] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX + 1, explicitGridPositionY);
	grids[2] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY + 1);
	grids[3] = (IETerrainBlock *)chunk->GetBlock(explicitGridPositionX - 1, explicitGridPositionY);

	grid->DelOldCalBorder(grids);
	grid->SetTerrainID(0);
	grid->SetDisplay(false);
}

void IETerrain::AddChild(int blockLocationX, int blockLocationY)
{
	m_alter = new IETerrainAlter();
	m_alter->_X = blockLocationX;
	m_alter->_Y = blockLocationY;
	m_alter->_TerrainInfo._TerrainID = m_readyTerrainID;
	m_alter->_TerrainInfo._TerrainMode = m_readyTerrainMode;
	m_alter->_TerrainInfo._Order = m_curOrder++;
	m_alters->Push(m_alter);

	switch (m_readyTerrainMode)
	{
	case __terrain_body_mode__:
		AddBody(m_readyTerrainID, m_readyTerrainMode, m_curOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_bevel_mode__:
		ApplyBevel(m_readyTerrainID, m_readyTerrainMode, m_curOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_piece_mode__:
		ApplyPiece(m_readyTerrainID, m_readyTerrainMode, m_curOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_none_mode__:
		ApplyNone(m_readyTerrainID, m_readyTerrainMode, m_curOrder, blockLocationX, blockLocationY);
		break;
	default:
		break;
	}
}

void IETerrain::RemoveChild(int blockLocationX, int blockLocationY)
{
	AddChild(blockLocationX, blockLocationY);
}

void IETerrain::AddBody(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString textureGroupName = IEString(terrainsInfo[terrainID]._TerrainName);

	if (terrainsInfo[terrainID]._BodyC)
	{
		int randIndex = rand() % terrainsInfo[terrainID]._BodyC;
		IETerrainBlock * grid = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY);
		if (grid != NULL)
		{
			m_alter->_TerrainInfoOld._Order = grid->GetOrder();
			m_alter->_TerrainInfoOld._TerrainID = grid->GetTerrainID();
			m_alter->_TerrainInfoOld._TerrainMode = grid->GetTerrainMODE();

			//RemoveChild(blockLocationX, blockLocationY);
			grid->Reload(terrainID, __terrain_body_mode__, createdOrder);
		}
		else if (grid == NULL)
		{
			return;

			m_alter->_TerrainInfoOld._TerrainMode = __terrain_none_mode__;

			grid = IETerrainBlock::Create(terrainID, __terrain_body_mode__, createdOrder);			//*** lua script 1400 ***//
			IEArea::AddChild(grid, blockLocationX, blockLocationY);
		}

		grid->ChangeTexture((textureGroupName + "/body_" + randIndex + ".png").GetString());	//*** glTexImage2D 40000 ***//

		//border part
		if (terrainsInfo[terrainID]._BorderC)
		{
			randIndex = rand() % terrainsInfo[terrainID]._BorderC;
			IETerrainBlock * grids[4];
			grids[0] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY - 1);
			grids[1] = (IETerrainBlock *)GetBlock(blockLocationX + 1, blockLocationY);
			grids[2] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY + 1);
			grids[3] = (IETerrainBlock *)GetBlock(blockLocationX - 1, blockLocationY);
			bool isBorderExits = false;
			for (int index = 0; index < 4; index++)
			{
				if (randIndex == -1)
				{
					grid->SetDisplayTerrainBorder(index, false);
				}
				if (grids[index] == NULL)
				{
					isBorderExits = true;
					grid->SetDisplayTerrainBorder(index, true);
				}
				else
				{
					if (grids[index]->GetTerrainMODE() == __terrain_none_mode__)
					{
						isBorderExits = true;
						grid->SetDisplayTerrainBorder(index, true);
					}
					else
					{
						if (!(grids[index]->ValidateTerrainID(terrainID)))
						{
							//必须创建的顺序大于隔壁(主要针对于map存储状况下的解决办法)
							if (grid->GetOrder() > grids[index]->GetOrder())
							{
								isBorderExits = true;
								grid->SetDisplayTerrainBorder(index, true);
								grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
							}
							else
							{
								grid->SetDisplayTerrainBorder(index, false);
							}
						}
						else
						{
							grid->SetDisplayTerrainBorder(index, false);
						}
					}
				}
			}
			if (isBorderExits && terrainsInfo[terrainID]._BorderC)
			{
				grid->SetBorderTextureFile((textureGroupName + "/border_" + randIndex + ".png").GetString());
			}
			else
			{
				grid->SetBorderTexture(NULL);
			}
		}
	}
}

void IETerrain::ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString s = IEString("texture/") + terrainsInfo[terrainID]._TerrainName;
	const char * terrainTextureName = s.GetString();

	IETerrainBlock * grids[4];
	grids[0] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY - 1);
	grids[1] = (IETerrainBlock *)GetBlock(blockLocationX + 1, blockLocationY);
	grids[2] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY + 1);
	grids[3] = (IETerrainBlock *)GetBlock(blockLocationX - 1, blockLocationY);

	bool allowSet = false;
	int surroundCount = 0;
	int surroundGridIndex = -1;
	for (int index = 0; index < 5; index++)
	{
		if (grids[index % 4])
		{
			surroundCount++;
			if (allowSet == true)
			{
				surroundGridIndex = index;
			}
			else
			{
				allowSet = true;
			}
		}
		else
		{
			allowSet = false;
		}
	}

	if (surroundCount == 2 && surroundGridIndex!=-1)
	{
		IETerrainBlock * grid = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY);
		if (grid != NULL)
		{
			RemoveChild(blockLocationX, blockLocationY);
		}

		IEString stringTexture = IEString(terrainTextureName) + "/bevel_" + (rand() % terrainsInfo[terrainID]._BevelC) + ".tga";
		grid = IETerrainBlock::Create(terrainID, terrainMODE, m_alter->_TerrainInfo._Order);
		IEArea::AddChild(grid, blockLocationX, blockLocationY);

		IETerrainBlock * grids[4];
		grids[0] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY - 1);
		grids[1] = (IETerrainBlock *)GetBlock(blockLocationX + 1, blockLocationY);
		grids[2] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY + 1);
		grids[3] = (IETerrainBlock *)GetBlock(blockLocationX - 1, blockLocationY);

		for (int index = 0; index < 4; index++)
		{
			grid->SetDisplayTerrainBorder(index, false);
		}

		for (int index = 0; index < 4; index++)
		{
			if (grids[index] != NULL)
			{
				grids[index]->SetDisplayTerrainBorder((index + 2) % 4, false);
			}
		}
	}
	else
	{
		return;
	}
}

void IETerrain::ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString s = IEString("texture/") + terrainsInfo[terrainID]._TerrainName;
	const char * terrainTextureName = s.GetString();

	IETerrainBlock * grid = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL && !grid->ValidateTerrainID(terrainID))
	{
		IEString stringTexture = IEString(terrainTextureName) + "/piece_" + (rand() % terrainsInfo[terrainID]._PieceC) + ".tga";
		grid->SetPieceSprite(stringTexture.GetString());
	}
}

void IETerrain::ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IETerrainBlock * grid = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY);
	if (grid == NULL)
	{
		m_curOrder--;
		m_alters->PopTop();
		return;
	}
	else
	{
		m_alter->_TerrainInfoOld._Order = grid->GetOrder();
		m_alter->_TerrainInfoOld._TerrainID = grid->GetTerrainID();
		m_alter->_TerrainInfoOld._TerrainMode = grid->GetTerrainMODE();

		RemoveChild(blockLocationX, blockLocationY);
	}

	//判定周围是否有需要复原的border
	IETerrainBlock * grids[4];
	grids[0] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY - 1);
	grids[1] = (IETerrainBlock *)GetBlock(blockLocationX + 1, blockLocationY);
	grids[2] = (IETerrainBlock *)GetBlock(blockLocationX, blockLocationY + 1);
	grids[3] = (IETerrainBlock *)GetBlock(blockLocationX - 1, blockLocationY);
	for (int index = 0; index < 4; index++)
	{
		if (grids[index] != NULL && grids[index]->ValidateTerrainGridMode(__terrain_body_mode__))
		{
			unsigned int terrainID = grids[index]->GetTerrainID();
			int randBorderIndex = rand() % terrainsInfo[terrainID]._BorderC;
			IEString terrainTextureName = IEString("texture/") + terrainsInfo[terrainID]._TerrainName;
			IEString stringTexture = terrainTextureName + "/border_" + randBorderIndex + ".png";
			grids[index]->SetBorderTextureFile(stringTexture.GetString());
			grids[index]->SetDisplayTerrainBorder((index + 2) % 4, true);
		}
	}
}

void IETerrain::RollbackAllAlters()
{
	while (IETerrainAlter * alter = (IETerrainAlter *)(m_alters->PopTop()))
	{

	}
}

void IETerrain::RollbackAlter()
{
	m_alter = (IETerrainAlter *)(m_alters->PopTop());

	if (!m_alter)
	{
		return;
	}

	unsigned int terrainID = m_alter->_TerrainInfoOld._TerrainID;
	IETerrainMode terrainMODE = m_alter->_TerrainInfoOld._TerrainMode;
	unsigned int createdOrder = m_alter->_TerrainInfoOld._Order;
	int blockLocationX = m_alter->_X;
	int blockLocationY = m_alter->_Y;

	switch (m_alter->_TerrainInfoOld._TerrainMode)
	{
	case __terrain_body_mode__:
		AddBody(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_bevel_mode__:
		ApplyBevel(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_piece_mode__:
		ApplyPiece(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_none_mode__:
		ApplyNone(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	default:
		break;
	}
}

void IETerrain::MouseMove(float x, float y)
{

}

void IETerrain::MouseChoose()
{

}

void IETerrain::MouseCancel()
{

}

void IETerrain::MouseClick()
{

}

void IETerrain::SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode)
{
	m_readyTerrainID = terrainID;
	m_readyTerrainMode = terrainMode;
}

IE_END