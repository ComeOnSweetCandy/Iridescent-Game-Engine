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
	case __terrain_bevel_mode__:
		ChangeBevel(blockLocationX, blockLocationY);
		break;
	case __terrain_piece_mode__:
		ChangePiece(blockLocationX, blockLocationY);
		break;
	default:
		break;
	}
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

	//for (int x = 0; x < m_chunkLength; x++)
	//{
	//	for (int y = 0; y < m_chunkLength; y++)
	//	{
	//		IETerrain * grid = (IETerrain *)gridArrays[x][y];
	//		if (grid->IsDisplayBorder())
	//		{
	//			index = rand() % m_terrainsInfo[grid->GetTerrainID()]._BorderC;

	//			m_loadString[0] = m_terrainsInfo[grid->GetTerrainID()]._TerrainName;
	//			m_loadString[2][0] = '0' + index;

	//			RESOURCE.InsertKeyStrings(m_loadString, 4);
	//			IETexture * texture = (IETexture *)(RESOURCE.GetCufFind());

	//			if (texture)
	//			{
	//				//grid->SetBorderTexture(texture);
	//			}
	//			else
	//			{
	//				char textureFile[64];

	//				sprintf(textureFile, "%s%s%d%s", m_terrainsInfo[grid->GetTerrainID()]._TerrainName, "/border_", index, ".png");
	//				//grid->SetBorderTextureFile(textureFile);
	//			}
	//		}
	//	}
	//}
}

IEChunk * IETerrainArea::CreateChunk()
{
	return IETerrainChunk::Create(m_chunkLength);
}

void IETerrainArea::LoadChunk(int blockX, int blockY)
{
	m_map->LoadTerrainChunk(blockX, blockY);
}

void IETerrainArea::LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder)
{
	int randIndex;

	if (m_terrainsInfo[terrainID]._BodyC)
	{
		randIndex = rand() % m_terrainsInfo[terrainID]._BodyC;

		IETerrain * grid = (IETerrain *)chunk->GetBlock(explicitGridPositionX, explicitGridPositionY);
		grid->Reload(terrainID, createdOrder); 

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

			//grid->AddNewCalBorder(grids);
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

	//grid->DelOldCalBorder(grids);
	grid->SetTerrainID(0);
	grid->SetDisplay(false);
}

void IETerrainArea::ChangeNone(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->Reload(0, 0);
		grid->ChangeBodyIndex(0);
	}
}

void IETerrainArea::ChangeBody(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->Reload(m_alter->_Terrain._TerrainID, m_alter->_Terrain._Order);
		grid->SetBlockPostion(blockLocationX, blockLocationY);
		grid->ChangeBodyIndex(m_alter->_Terrain._TerrainID);
		grid->ChangeBorderIndex(m_alter->_Terrain._TerrainID);
	}
}

void IETerrainArea::ChangeBevel(int blockLocationX, int blockLocationY)
{

}

void IETerrainArea::ChangePiece(int blockLocationX, int blockLocationY)
{
	IETerrain * grid = (IETerrain *)GetBlock(blockLocationX, blockLocationY);
	if (grid != NULL)
	{
		grid->ChangePieceIndex(m_alter->_Terrain._TerrainID);
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

		break;
	case __terrain_none_mode__:

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
		m_suspension->Visit();
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