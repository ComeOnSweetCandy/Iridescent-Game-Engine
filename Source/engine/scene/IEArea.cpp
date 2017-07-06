#define __IE_DLL_EXPORTS__
#include "IEArea.h"

IE_BEGIN

IEArea::IEArea()
{
	m_sceneType = __ie_scene_none__;
	m_visibleRadius = 0;
	m_visibleChunksCount = 1;
	m_chunkLength = 1;

	m_chunksIndexMatrix = NULL;
	m_chunks = NULL;

	m_alters = NULL;
	m_moveThing = NULL;

	m_centerChunkLocation = IEGrid(0, 0);
}

IEArea::~IEArea()
{
	__IE_RELEASE__(m_alters);

	ClearChunks();
}

void IEArea::Initialization(IEMap * map, int visibleRadius, int chunkLength)
{
	IELayer::Initialization();

	m_map = map;
	m_visibleRadius = visibleRadius;
	m_chunkLength = chunkLength;
	m_visibleLength = m_visibleRadius * 2 + 1;
	m_visibleChunksCount = m_visibleLength * m_visibleLength;
	m_alters = IEContainer::CreateAndRetain();

	IEArea::InitChunks();
	IEArea::SetCenterChunkLocation(0, 0);
}

IEArea * IEArea::Create(IEMap * map, int visibleRadius, int sideLength)
{
	IEArea * object = new IEArea();
	object->Initialization(map, visibleRadius, sideLength);
	return object;
}

void IEArea::SetCenterBlockLocation(int blockLocationX, int blockLocationY)
{
	static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
	LocationTranslate(blockLocationX, blockLocationY, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

	if (m_centerChunkLocation.m_x != chunkLocationX && m_centerChunkLocation.m_y != chunkLocationY)
	{
		SetCenterChunkLocation(chunkLocationX, chunkLocationY);
	}
}

void IEArea::SetCenterChunkLocation(int chunkLocationX, int chunkLocationY)
{
	//设定中心chunk
	m_centerChunkLocation = IEGrid(chunkLocationX, chunkLocationY);

	for (int chunkX = -m_visibleRadius; chunkX <= m_visibleRadius; chunkX++)
	{
		for (int chunkY = -m_visibleRadius; chunkY <= m_visibleRadius; chunkY++)
		{
			m_chunksIndexMatrix[m_visibleRadius + chunkX][m_visibleRadius + chunkY]->_ChunkLocation = m_centerChunkLocation + IEGrid(chunkX, chunkY);
			m_chunksIndexMatrix[m_visibleRadius + chunkX][m_visibleRadius + chunkY]->_Chunk = NULL;
		}
	}

	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		if (m_chunks[index]->_Using)
		{
			IEGrid offset = m_chunks[index]->_ChunkLocation - m_centerChunkLocation;
			IEGrid absOffset = offset.Absolute();

			if (absOffset.m_x > m_visibleRadius || absOffset.m_y > m_visibleRadius)
			{
				m_chunks[index]->_Using = false;
			}
			else
			{
				m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk = m_chunks[index]->_Chunk;
			}
		}
	}

	int index = 0;
	for (int blockX = -m_visibleRadius; blockX <= m_visibleRadius; blockX++)
	{
		for (int blockY = -m_visibleRadius; blockY <= m_visibleRadius; blockY++)
		{
			if (m_chunksIndexMatrix[m_visibleRadius + blockX][m_visibleRadius + blockY]->_Chunk == NULL)
			{
				while (index < m_visibleChunksCount && m_chunks[index]->_Using == true)
				{
					index++;
				}

				IEGrid blockGrid = m_chunksIndexMatrix[m_visibleRadius + blockX][m_visibleRadius + blockY]->_ChunkLocation;

				m_chunksIndexMatrix[m_visibleRadius + blockX][m_visibleRadius + blockY]->_Chunk = m_chunks[index]->_Chunk;

				m_chunks[index]->_Chunk->SetLocation(blockGrid.m_x, blockGrid.m_y);
				m_chunks[index]->_Chunk->SetTranslate(blockGrid.m_x * m_chunkLength, blockGrid.m_y * m_chunkLength);
				m_chunks[index]->_ChunkLocation = blockGrid;
				m_chunks[index]->_Using = true;

				LoadChunk(blockGrid.m_x, blockGrid.m_y);
			}
		}
	}
}

IEBlock * IEArea::GetBlock(int blockLocationX, int blockLocationY)
{
	static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
	LocationTranslate(blockLocationX, blockLocationY, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

	IEChunk * chunk = GetChunk(chunkLocationX, chunkLocationY);
	if (chunk)
	{
		IEBlock * block = chunk->GetBlock(explicitBlockLocationX, explicitBlockLocationY);
		return block;
	}
	return NULL;
}

IEChunk * IEArea::GetChunk(int chunkLocationX, int chunkLocationY)
{
	chunkLocationX = chunkLocationX - m_centerChunkLocation.m_x + m_visibleRadius;
	chunkLocationY = chunkLocationY - m_centerChunkLocation.m_y + m_visibleRadius;

	if (chunkLocationX >= 0 && chunkLocationX < m_visibleLength && chunkLocationY >= 0 && chunkLocationY < m_visibleLength)
	{
		return m_chunksIndexMatrix[chunkLocationX][chunkLocationY]->_Chunk;
	}
	else
	{
		//__IE_WARNING__("IEArea : GetChunk : out of range.\n");
		return NULL;
	}
}

IEContainer * IEArea::GetAlters()
{
	return m_alters;
}

IEMap * IEArea::GetBindedMap()
{
	return m_map;
}

void IEArea::LoadChunks()
{
	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		IEGrid chunkLocation = m_chunks[index]->_ChunkLocation;
		LoadChunk(chunkLocation.m_x, chunkLocation.m_y);
	}
}

void IEArea::LoadChunk(int chunkLocationX, int chunkLocationY)
{

}

void IEArea::ClearChunks()
{
	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		if (m_chunks[index])
		{
			if (m_chunks[index]->_Chunk)
			{
				m_chunks[index]->_Chunk->Release();
				m_chunks[index]->_Chunk = NULL;
			}
			delete m_chunks[index];
			m_chunks[index] = NULL;
		}
	}
	delete[] m_chunks;

	for (int blockX = 0; blockX < m_visibleLength; blockX++)
	{
		for (int blockY = 0; blockY < m_visibleLength; blockY++)
		{
			if (m_chunksIndexMatrix[blockX][blockY])
			{
				m_chunksIndexMatrix[blockX][blockY]->_Chunk = NULL;
				delete m_chunksIndexMatrix[blockX][blockY];
				m_chunksIndexMatrix[blockX][blockY] = NULL;
			}
		}
		delete[] m_chunksIndexMatrix[blockX];
	}
	delete[] m_chunksIndexMatrix;
}

void IEArea::Visit()
{
	ChangeModelMatrix();
	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		glPushMatrix();
		m_chunks[index]->_Chunk->Visit();
		glPopMatrix();
	}
	RevertModelMatrix();
}

void IEArea::AddChild(IEBlock * block, int blockLocationX, int blockLocationY)
{
	static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
	LocationTranslate(blockLocationX, blockLocationY, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

	IEChunk * chunk = GetChunk(chunkLocationX, chunkLocationY);
	if (chunk)
	{
		chunk->AddChild(block, explicitBlockLocationX, explicitBlockLocationY);
	}
	else
	{
		__IE_WARNING__("IEArea : AddChild warning , out of range.\n");
	}
}

void IEArea::StanceChild(IEBlock * block, int blockLocationX, int blockLocationY)
{
	static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
	LocationTranslate(blockLocationX, blockLocationY, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

	IEChunk * chunk = GetChunk(chunkLocationX, chunkLocationY);
	if (chunk)
	{
		chunk->StanceChild(block, explicitBlockLocationX, explicitBlockLocationY);
	}
	else
	{
		__IE_WARNING__("IEArea : StanceChild warning , out of range.\n");
	}
}

void IEArea::RemoveChild(int blockLocationX, int blockLocationY)
{
	static int chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY;
	LocationTranslate(blockLocationX, blockLocationY, chunkLocationX, chunkLocationY, explicitBlockLocationX, explicitBlockLocationY);

	IEChunk * chunk = GetChunk(chunkLocationX, chunkLocationY);
	if (chunk)
	{
		chunk->RemoveChild(explicitBlockLocationX, explicitBlockLocationY);
	}
	else
	{
		__IE_WARNING__("IEArea : RemoveChild warning , out of range.\n");
	}
}

IEChunk * IEArea::CreateChunk()
{
	return IEChunk::Create(m_chunkLength);
}

void IEArea::SetCurOrder(unsigned int order)
{
	m_curOrder = order;
}

unsigned int IEArea::GetCurOrder()
{
	return m_curOrder;
}

void IEArea::MouseMove(float x, float y)
{
	//在这里计算鼠标所指向的位置 chunk block都会被记录下来

}

void IEArea::LocationTranslate(int blockLocationX, int blockLocationY, int& chunkLocationX, int& chunkLocationY, int& explicitLocationX, int& explicitLocationY)
{
	explicitLocationX = blockLocationX % m_chunkLength;
	explicitLocationY = blockLocationY % m_chunkLength;
	if (explicitLocationX < 0)
	{
		explicitLocationX = explicitLocationX + m_chunkLength;
	}
	if (explicitLocationY < 0)
	{
		explicitLocationY = explicitLocationY + m_chunkLength;
	}

	if (blockLocationX < 0)
	{
		blockLocationX = blockLocationX + 1 - m_chunkLength;
	}
	if (blockLocationY < 0)
	{
		blockLocationY = blockLocationY + 1 - m_chunkLength;
	}

	chunkLocationX = blockLocationX / m_chunkLength;
	chunkLocationY = blockLocationY / m_chunkLength;
}

void IEArea::InitChunks()
{
	m_chunks = new IEChunkUnit *[m_visibleChunksCount];
	m_chunksIndexMatrix = new IEChunkUnit **[m_visibleLength];

	for (int index = 0; index < m_visibleLength; index++)
	{
		m_chunksIndexMatrix[index] = new IEChunkUnit *[m_visibleLength];
	}
	for (int blockX = 0; blockX < m_visibleLength; blockX++)
	{
		for (int blockY = 0; blockY < m_visibleLength; blockY++)
		{
			m_chunksIndexMatrix[blockX][blockY] = new IEChunkUnit();
		}
	}
	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		m_chunks[index] = new IEChunkUnit();
		m_chunks[index]->_Using = false;
		m_chunks[index]->_Chunk = CreateChunk();
		m_chunks[index]->_Chunk->BindArea(this);
		m_chunks[index]->_Chunk->Retain();
	}
}

IE_END