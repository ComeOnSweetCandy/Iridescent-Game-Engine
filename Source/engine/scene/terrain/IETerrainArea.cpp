#define __IE_DLL_EXPORTS__
#include "IETerrainArea.h"

IE_BEGIN

IETerrainArea::IETerrainArea()
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

IETerrainArea::~IETerrainArea()
{

}

void IETerrainArea::Initialization(IEMap * map, int visibleRadius, int sideLength)
{
	IEArea::Initialization(map, visibleRadius, sideLength);

	m_terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
}

IETerrainArea * IETerrainArea::Create(IEMap * map, int visibleRadius, int sideLength)
{
	IETerrainArea * terrain = new IETerrainArea();
	terrain->Initialization(map, visibleRadius, sideLength);
	return terrain;
}

void IETerrainArea::AddChild(int blockLocationX, int blockLocationY)
{
	m_alter = new IETerrainAlter();
	m_alters->Push(m_alter);

	//先记载入新的信息
	m_alter->_X = blockLocationX;
	m_alter->_Y = blockLocationY;
	m_alter->_Terrain._TerrainID = m_readyTerrainID;
	m_alter->_Terrain._TerrainMode = m_readyTerrainMode;
	m_alter->_Terrain._Order = m_curOrder++;

	//放入旧的信息
	if (IETerrain * pastTerrain = (IETerrain *)(GetBlock(blockLocationX, blockLocationY)))
	{
		m_alter->_TerrainPast._TerrainID = pastTerrain->GetTerrainID();
		m_alter->_TerrainPast._TerrainMode = pastTerrain->GetTerrainMODE();
		m_alter->_TerrainPast._Order = pastTerrain->GetOrder();
	}
	else
	{
		m_alter->_TerrainPast._TerrainID = 0;
		m_alter->_TerrainPast._TerrainMode = __terrain_none_mode__;
		m_alter->_TerrainPast._Order = 0;
	}

	switch (m_readyTerrainMode)
	{
	case __terrain_none_mode__:
		ChangeNone(blockLocationX, blockLocationY);
		break;
	case __terrain_body_mode__:
		ChangeBody(blockLocationX, blockLocationY);
		break;
	default:
		break;
	}
}

IEChunk * IETerrainArea::CreateChunk()
{
	return IETerrainChunk::Create(m_chunkLength);
}

void IETerrainArea::LoadChunk(int blockX, int blockY)
{
	m_map->LoadTerrainChunk(blockX, blockY);
}

void IETerrainArea::LoadChilds(IETerrainBlockFormat * blocks, int chunkLocationX, int chunkLocationY)
{
	IETerrainChunk * chunk = (IETerrainChunk *)GetChunk(chunkLocationX, chunkLocationY);
	chunk->ResetCache();

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
					LoadBody(chunk, x, y, blocks[index]._TerrainID, blocks[index]._Order);
				}
				else if (blocks[index]._TerrainMode == __terrain_none_mode__)
				{
					LoadNone(chunk, x, y, 0, 0);
				}

				index++;
			}
			else
			{
				LoadNone(chunk, x, y, 0, 0);
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
	//		if (alters[index]->_Terrain._TerrainMode == __terrain_body_mode__)
	//		{
	//			LoadBody(block, alters[index]->_explicitBlockLocationX, alters[index]->_explicitBlockLocationY, alters[index]->_Terrain._TerrainID, alters[index]->_Terrain._Order);
	//		}
	//		else if (alters[index]->_Terrain._TerrainMode == __terrain_none_mode__)
	//		{
	//			LoadNone(block, alters[index]->_explicitBlockLocationX, alters[index]->_explicitBlockLocationY, 0, 0);
	//		}
	//	}
	//}

	//设置border sprite
	IEBlock *** gridArrays = chunk->GetBlocksMatrix();
	m_loadString[0];
	m_loadString[1] = stringBorder;
	m_loadString[2] = stringNumber;
	m_loadString[3] = stringPNG;
	
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IETerrain * grid = (IETerrain *)gridArrays[x][y];
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

void IETerrainArea::LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder)
{
	int randIndex;

	if (m_terrainsInfo[terrainID]._BodyC)
	{
		randIndex = rand() % m_terrainsInfo[terrainID]._BodyC;

		IETerrain * grid = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY);
		grid->Reload(terrainID, __terrain_body_mode__, createdOrder); 

		m_loadString[0] = m_terrainsInfo[terrainID]._TerrainName;
		m_loadString[2][0] = '0' + randIndex;

		RESOURCE.InsertKeyStrings(m_loadString, 4);
		IEPackerTexture * texture = (IEPackerTexture *)(RESOURCE.GetCufFind());

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
			IETerrain * grids[4];
			grids[0] = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY - 1);
			grids[1] = (IETerrain *)chunk->GetBlock(explicitGridPositionX + 1, explicitGridPositionY);
			grids[2] = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY + 1);
			grids[3] = (IETerrain *)chunk->GetBlock(explicitGridPositionX - 1, explicitGridPositionY);

			grid->AddNewCalBorder(grids);
		}
	}
}

void IETerrainArea::LoadNone(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder)
{
	IETerrain * grid = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY);
	IETerrain * grids[4];

	grids[0] = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY - 1);
	grids[1] = (IETerrain *)chunk->GetBlock(explicitGridPositionX + 1, explicitGridPositionY);
	grids[2] = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY + 1);
	grids[3] = (IETerrain *)chunk->GetBlock(explicitGridPositionX - 1, explicitGridPositionY);

	grid->DelOldCalBorder(grids);
	grid->SetTerrainID(0);
	grid->SetDisplay(false);
}

void IETerrainArea::ChangeBody(int blockLocationX, int blockLocationY)
{
	IETerrainAlterInfo &_terrain = m_alter->_Terrain;
	IETerrainAlterInfo &_terrainPast = m_alter->_TerrainPast;

	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString textureGroupName = IEString(terrainsInfo[_terrain._TerrainID]._TerrainName);

	if (terrainsInfo[_terrain._TerrainID]._BodyC)
	{
		int randIndex = rand() % terrainsInfo[_terrain._TerrainID]._BodyC;
		IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
		if (grid != NULL)
		{
			grid->Reload(_terrain._TerrainID, __terrain_body_mode__, _terrain._Order);
		}

		//grid->ChangeTexture((textureGroupName + "/body_" + randIndex + ".png").GetString());	//*** glTexImage2D 40000 ***//

		//border part
		if (terrainsInfo[_terrain._TerrainID]._BorderC)
		{
			randIndex = rand() % terrainsInfo[_terrain._TerrainID]._BorderC;
			IETerrain * grids[4];
			grids[0] = (IETerrain *)GetBlock(blockLocationX, blockLocationY - 1);
			grids[1] = (IETerrain *)GetBlock(blockLocationX + 1, blockLocationY);
			grids[2] = (IETerrain *)GetBlock(blockLocationX, blockLocationY + 1);
			grids[3] = (IETerrain *)GetBlock(blockLocationX - 1, blockLocationY);
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
						if (grids[index]->GetTerrainID() != _terrain._TerrainID)
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
			if (isBorderExits && terrainsInfo[_terrain._TerrainID]._BorderC)
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

void IETerrainArea::ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString s = IEString("texture/") + terrainsInfo[terrainID]._TerrainName;
	const char * terrainTextureName = s.GetString();

	IETerrain * grids[4];
	grids[0] = (IETerrain *)GetBlock(blockLocationX, blockLocationY - 1);
	grids[1] = (IETerrain *)GetBlock(blockLocationX + 1, blockLocationY);
	grids[2] = (IETerrain *)GetBlock(blockLocationX, blockLocationY + 1);
	grids[3] = (IETerrain *)GetBlock(blockLocationX - 1, blockLocationY);

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
		IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
		if (grid != NULL)
		{
			RemoveChild(blockLocationX, blockLocationY);
		}

		IEString stringTexture = IEString(terrainTextureName) + "/bevel_" + (rand() % terrainsInfo[terrainID]._BevelC) + ".tga";
		grid = IETerrain::Create(terrainID, terrainMODE, m_alter->_Terrain._Order);
		IEArea::AddChild(grid, blockLocationX, blockLocationY);

		IETerrain * grids[4];
		grids[0] = (IETerrain *)GetBlock(blockLocationX, blockLocationY - 1);
		grids[1] = (IETerrain *)GetBlock(blockLocationX + 1, blockLocationY);
		grids[2] = (IETerrain *)GetBlock(blockLocationX, blockLocationY + 1);
		grids[3] = (IETerrain *)GetBlock(blockLocationX - 1, blockLocationY);

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

void IETerrainArea::ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IEString s = IEString("texture/") + terrainsInfo[terrainID]._TerrainName;
	const char * terrainTextureName = s.GetString();

	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL && grid->GetTerrainID() != terrainID)
	{
		IEString stringTexture = IEString(terrainTextureName) + "/piece_" + (rand() % terrainsInfo[terrainID]._PieceC) + ".tga";
		grid->SetPieceSprite(stringTexture.GetString());
	}
}

void IETerrainArea::ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int gridOrder, int blockLocationX, int blockLocationY)
{
	IETerrainInfo * terrainsInfo = IETerrainsInfoManager::Share()->GetTerrainsInfoList();
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid == NULL)
	{
		m_curOrder--;
		m_alters->PopTop();
		return;
	}
	else
	{
		m_alter->_TerrainPast._Order = grid->GetOrder();
		m_alter->_TerrainPast._TerrainID = grid->GetTerrainID();
		m_alter->_TerrainPast._TerrainMode = grid->GetTerrainMODE();

		RemoveChild(blockLocationX, blockLocationY);
	}

	//判定周围是否有需要复原的border
	IETerrain * grids[4];
	grids[0] = (IETerrain *)GetBlock(blockLocationX, blockLocationY - 1);
	grids[1] = (IETerrain *)GetBlock(blockLocationX + 1, blockLocationY);
	grids[2] = (IETerrain *)GetBlock(blockLocationX, blockLocationY + 1);
	grids[3] = (IETerrain *)GetBlock(blockLocationX - 1, blockLocationY);
	for (int index = 0; index < 4; index++)
	{
		if (grids[index] != NULL && grids[index]->GetTerrainMODE() == __terrain_body_mode__)
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

void IETerrainArea::RollbackAllAlters()
{
	while (IETerrainAlter * alter = (IETerrainAlter *)(m_alters->PopTop()))
	{

	}
}

void IETerrainArea::RollbackAlter()
{
	m_alter = (IETerrainAlter *)(m_alters->PopTop());

	if (!m_alter)
	{
		return;
	}

	unsigned int terrainID = m_alter->_TerrainPast._TerrainID;
	IETerrainMode terrainMODE = m_alter->_TerrainPast._TerrainMode;
	unsigned int createdOrder = m_alter->_TerrainPast._Order;
	int blockLocationX = m_alter->_X;
	int blockLocationY = m_alter->_Y;

	switch (m_alter->_TerrainPast._TerrainMode)
	{
	case __terrain_body_mode__:
		AddBody(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	case __terrain_none_mode__:
		ApplyNone(terrainID, terrainMODE, createdOrder, blockLocationX, blockLocationY);
		break;
	default:
		break;
	}
}

void IETerrainArea::MouseMove(float x, float y)
{
	//首先计算鼠标所指向的格子和小格子
	float revisePositionX = IESituation::Share()->_MousePositionX;
	float revisePositionY = IESituation::Share()->_MousePositionY;
	if (revisePositionX < 0.0f)
	{
		revisePositionX = revisePositionX - 1.0f;
	}
	if (revisePositionY < 0.0f)
	{
		revisePositionY = revisePositionY - 1.0f;
	}
	m_mouseLocation = IEGrid(revisePositionX, revisePositionY);

	//在这里计算鼠标所指向的位置 chunk block都会被记录下来
	if (m_readyTerrainID != 0 && m_readyTerrainMode != __terrain_none_mode__)
	{
		//说明已经选择了ReadyID
		m_suspension->SetTranslate(m_mouseLocation.m_x, m_mouseLocation.m_y);
		//m_suspension->Visit();
	}
	else
	{
		//说明没有选择ReadyID 那么就以当前地面为显示的元素
		if (IETerrain * terrain = (IETerrain *)GetBlock(m_mouseLocation.m_x, m_mouseLocation.m_y))
		{
			IEPackerTexture * texture = terrain->GetTexture();
			m_suspension->ChangeTexture(texture);
			m_suspension->ChangeGroup("body");
			m_suspension->SetTranslate(x, y);
		}
		else
		{
			m_suspension->RemoveTexture();
		}
	}
}

void IETerrainArea::MouseCancel()
{
	m_readyTerrainID = 0;
	m_readyTerrainMode = __terrain_none_mode__;
}

void IETerrainArea::MouseClick()
{
	//首先查看当前的模式
	if (m_readyTerrainID == 0)
	{
		//选择模式 对当前位置进行选择
		m_choosen = GetBlock(m_mouseLocation.m_x, m_mouseLocation.m_y);

		//会在一片地区显示choosen的所有的信息 编辑器下会显示
	}
	else
	{
		AddChild(m_mouseLocation.m_x, m_mouseLocation.m_y);
	}
}

void IETerrainArea::SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode)
{
	m_readyTerrainID = terrainID;
	m_readyTerrainMode = terrainMode;

	if (m_readyTerrainID != 0 && m_readyTerrainMode != __terrain_none_mode__)
	{
		IEPackerTexture * texture = IEPackerTexture::Create(m_terrainsInfo[m_readyTerrainID]._Xml->FindChild("texture"));
		m_suspension->ChangeTexture(texture);
		m_suspension->ChangeGroup("body");
	}
}

IE_END