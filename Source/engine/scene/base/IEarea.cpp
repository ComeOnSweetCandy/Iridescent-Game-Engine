#define __IE_DLL_EXPORTS__
#include "IEarea.h"

IE_BEGIN

IEArea::IEArea()
{
	m_visibleRadius = 1;
	m_maxBlocksCount = 1;
	m_sideLength = 1;

	m_blocksMatrix = NULL;
	m_blocksIndex = NULL;
	m_alters = NULL;

	m_centerChunkLocation = IEGrid(0, 0);
}

IEArea::~IEArea()
{
	__IE_RELEASE__(m_alters);

	ClearChunks();
}

void IEArea::Initialization(IEMap * map, int visibleRadius, int sideLength)
{
	IELayer::Initialization();

	m_map = map;
	m_visibleRadius = visibleRadius;
	m_sideLength = sideLength;
	m_alters = IEContainer::CreateAndRetain();

	InitViewChunks();
	SetCenterChunkLocation(IEGrid(0, 0));
}

IEArea * IEArea::Create(IEMap * map, int visibleRadius, int sideLength)
{
	IEArea * object = new IEArea();
	object->Initialization(map, visibleRadius, sideLength);
	return object;
}

IEBlock * IEArea::GetBlock(int blockLocationX, int blockLocationY)
{
	IEGrid chunkLocation;
	IEGrid explicitBlockLocation;
	LocationTranslate(IEGrid(blockLocationX, blockLocationY), chunkLocation, explicitBlockLocation);

	IEGrid offset = chunkLocation - m_centerChunkLocation;
	if (!legalRange(offset))
	{
		return NULL;
	}

	IEChunk * chunk = m_blocksMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
	if (!chunk)
	{
		return NULL;
	}
	IEBlock * block = chunk->GetBlock(explicitBlockLocation.m_x, explicitBlockLocation.m_y);
	return block;
}

IEChunk * IEArea::GetChunk(int chunkLocationX, int chunkLocationY)
{
	chunkLocationX = chunkLocationX - m_centerChunkLocation.m_x + m_visibleRadius;
	chunkLocationY = chunkLocationY - m_centerChunkLocation.m_y + m_visibleRadius;

	if (chunkLocationX >= 0 && chunkLocationX <= m_visibleRadius * 2 && chunkLocationY >= 0 && chunkLocationY <= m_visibleRadius * 2)
	{
		return m_blocksMatrix[chunkLocationX][chunkLocationY]->_Chunk;
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

void IEArea::LocationTranslate(IEGrid blockLocation, IEGrid& chunkLocation, IEGrid& explicitBlockLocation)
{
	explicitBlockLocation.m_x = blockLocation.m_x % m_sideLength;
	explicitBlockLocation.m_y = blockLocation.m_y % m_sideLength;
	if (explicitBlockLocation.m_x < 0)
	{
		explicitBlockLocation.m_x = explicitBlockLocation.m_x + m_sideLength;
	}
	if (explicitBlockLocation.m_y < 0)
	{
		explicitBlockLocation.m_y = explicitBlockLocation.m_y + m_sideLength;
	}

	if (blockLocation.m_x < 0)
	{
		blockLocation.m_x = blockLocation.m_x + 1 - m_sideLength;
	}
	if (blockLocation.m_y < 0)
	{
		blockLocation.m_y = blockLocation.m_y + 1 - m_sideLength;
	}

	chunkLocation.m_x = blockLocation.m_x / m_sideLength;
	chunkLocation.m_y = blockLocation.m_y / m_sideLength;
}

void IEArea::LocationTranslate(int blockLocationX, int blockLocationY, int& chunkLocationX, int& chunkLocationY, int& explicitLocationX, int& explicitLocationY)
{
	explicitLocationX = blockLocationX % m_sideLength;
	explicitLocationY = blockLocationY % m_sideLength;
	if (explicitLocationX < 0)
	{
		explicitLocationX = explicitLocationX + m_sideLength;
	}
	if (explicitLocationY < 0)
	{
		explicitLocationY = explicitLocationY + m_sideLength;
	}

	if (blockLocationX < 0)
	{
		blockLocationX = blockLocationX + 1 - m_sideLength;
	}
	if (blockLocationY < 0)
	{
		blockLocationY = blockLocationY + 1 - m_sideLength;
	}

	chunkLocationX = blockLocationX / m_sideLength;
	chunkLocationY = blockLocationY / m_sideLength;
}

void IEArea::InitViewChunks()
{
	int lineMaxBlock = m_visibleRadius * 2 + 1;
	m_maxBlocksCount = lineMaxBlock * lineMaxBlock;
	m_blocksIndex = new IEBlockUnit *[m_maxBlocksCount];

	m_blocksMatrix = new IEBlockUnit **[lineMaxBlock];
	for (int index = 0; index < lineMaxBlock; index++)
	{
		m_blocksMatrix[index] = new IEBlockUnit *[lineMaxBlock];
	}
	for (int blockX = 0; blockX < lineMaxBlock; blockX++)
	{
		for (int blockY = 0; blockY < lineMaxBlock; blockY++)
		{
			m_blocksMatrix[blockX][blockY] = new IEBlockUnit();
		}
	}
	for (int index = 0; index < m_maxBlocksCount; index++)
	{
		m_blocksIndex[index] = new IEBlockUnit();
		m_blocksIndex[index]->_Using = false;
		m_blocksIndex[index]->_Chunk = CreateChunk();
		m_blocksIndex[index]->_Chunk->BindArea(this);
		m_blocksIndex[index]->_Chunk->Retain();
	}
}

void IEArea::SetCenterChunkLocation(IEGrid centerBlock)
{
	IEGrid m_oldCenterBlock = m_centerChunkLocation;
	m_centerChunkLocation = centerBlock;
	int viewHalfBlock = m_visibleRadius;

	for (int blockX = -viewHalfBlock; blockX <= viewHalfBlock; blockX++)
	{
		for (int blockY = -viewHalfBlock; blockY <= viewHalfBlock; blockY++)
		{
			m_blocksMatrix[viewHalfBlock + blockX][viewHalfBlock + blockY]->_ChunkLocation = m_centerChunkLocation + IEGrid(blockX, blockY);
			m_blocksMatrix[viewHalfBlock + blockX][viewHalfBlock + blockY]->_Chunk = NULL;
		}
	}

	for (int index = 0; index < m_maxBlocksCount; index++)
	{
		if (m_blocksIndex[index]->_Using)
		{
			IEGrid offset = m_blocksIndex[index]->_ChunkLocation - m_centerChunkLocation;
			IEGrid absOffset = offset.Absolute();

			if (absOffset.m_x > m_visibleRadius || absOffset.m_y > m_visibleRadius)
			{
				m_blocksIndex[index]->_Using = false;
			}
			else
			{
				m_blocksMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk = m_blocksIndex[index]->_Chunk;
			}
		}
	}

	int index = 0;
	for (int blockX = -viewHalfBlock; blockX <= viewHalfBlock; blockX++)
	{
		for (int blockY = -viewHalfBlock; blockY <= viewHalfBlock; blockY++)
		{
			if (m_blocksMatrix[viewHalfBlock + blockX][viewHalfBlock + blockY]->_Chunk == NULL)
			{
				while (index < m_maxBlocksCount && m_blocksIndex[index]->_Using == true)
				{
					index++;
				}

				IEGrid blockGrid = m_blocksMatrix[viewHalfBlock + blockX][viewHalfBlock + blockY]->_ChunkLocation;

				m_blocksMatrix[viewHalfBlock + blockX][viewHalfBlock + blockY]->_Chunk = m_blocksIndex[index]->_Chunk;

				m_blocksIndex[index]->_Chunk->SetLocation(blockGrid.m_x, blockGrid.m_y);
				m_blocksIndex[index]->_Chunk->SetTranslate(blockGrid.m_x * m_sideLength, blockGrid.m_y * m_sideLength);
				m_blocksIndex[index]->_ChunkLocation = blockGrid;
				m_blocksIndex[index]->_Using = true;
				
				LoadChunk(blockGrid.m_x, blockGrid.m_y);
			}
		}
	}
}

void IEArea::SetCenterBlockLocation(IEGrid centerWorld)
{
	IEGrid chunkLocation;
	IEGrid explicitBlockLocation;

	LocationTranslate(centerWorld, chunkLocation, explicitBlockLocation);

	if (chunkLocation != m_centerChunkLocation)
	{
		SetCenterChunkLocation(chunkLocation);
	}
}

IEChunk * IEArea::CreateChunk()
{
	return IEChunk::Create(m_sideLength);
}

void IEArea::LoadChunks()
{
	for (int index = 0; index < m_maxBlocksCount; index++)
	{
		IEGrid chunkLocation = m_blocksIndex[index]->_ChunkLocation;
		LoadChunk(chunkLocation.m_x, chunkLocation.m_y);
	}
}

void IEArea::LoadChunk(int chunkLocationX, int chunkLocationY)
{

}

void IEArea::ClearChunks()
{
	for (int index = 0; index < m_maxBlocksCount; index++)
	{
		if (m_blocksIndex[index])
		{
			if (m_blocksIndex[index]->_Chunk)
			{
				m_blocksIndex[index]->_Chunk->Release();
				m_blocksIndex[index]->_Chunk = NULL;
			}
			delete m_blocksIndex[index];
			m_blocksIndex[index] = NULL;
		}
	}
	delete[] m_blocksIndex;

	int lineMaxBlock = m_visibleRadius * 2 + 1;
	for (int blockX = 0; blockX < lineMaxBlock; blockX++)
	{
		for (int blockY = 0; blockY < lineMaxBlock; blockY++)
		{
			if (m_blocksMatrix[blockX][blockY])
			{
				m_blocksMatrix[blockX][blockY]->_Chunk = NULL;
				delete m_blocksMatrix[blockX][blockY];
				m_blocksMatrix[blockX][blockY] = NULL;
			}
		}
		delete[] m_blocksMatrix[blockX];
	}
	delete[] m_blocksMatrix;
}

void IEArea::Visit()
{
	ChangeModelMatrix();
	for (int index = 0; index < m_maxBlocksCount; index++)
	{
		glPushMatrix();
		m_blocksIndex[index]->_Chunk->Visit();
		glPopMatrix();
	}
	RevertModelMatrix();
}

IEMap * IEArea::GetBindedMap()
{
	return m_map;
}

void IEArea::AddChild(IEBlock * block, int blockLocationX, int blockLocationY)
{
	IEGrid chunkLocation;
	IEGrid explicitBlockLocation;

	LocationTranslate(IEGrid(blockLocationX, blockLocationY), chunkLocation, explicitBlockLocation);
	IEGrid offset = chunkLocation - m_centerChunkLocation;

	if (!legalRange(offset))
	{
		return;
	}
	m_blocksMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk->AddChild(block, explicitBlockLocation.m_x, explicitBlockLocation.m_y);
}

void IEArea::StanceChild(IEBlock * block, int blockLocationX, int blockLocationY)
{
	IEGrid chunkLocation;
	IEGrid explicitBlockLocation;

	LocationTranslate(IEGrid(blockLocationX, blockLocationY), chunkLocation, explicitBlockLocation);
	IEGrid offset = chunkLocation - m_centerChunkLocation;

	if (!legalRange(offset))
	{
		return;
	}
	m_blocksMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk->StanceChild(block, explicitBlockLocation.m_x, explicitBlockLocation.m_y);
}

void IEArea::RemoveChild(int blockLocationX, int blockLocationY)
{
	IEGrid chunkLocation;
	IEGrid explicitBlockLocation;

	LocationTranslate(IEGrid(blockLocationX, blockLocationY), chunkLocation, explicitBlockLocation);
	IEGrid offset = chunkLocation - m_centerChunkLocation;

	if (!legalRange(offset))
	{
		return;
	}

	m_blocksMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk->RemoveChild(explicitBlockLocation.m_x, explicitBlockLocation.m_y);
}

void IEArea::SetCurOrder(unsigned int order)
{
	m_curOrder = order;
}

unsigned int IEArea::GetCurOrder()
{
	return m_curOrder;
}

bool IEArea::legalRange(IEGrid chunkLocation)
{
	chunkLocation = chunkLocation.Absolute();
	if (chunkLocation.m_x > m_visibleRadius || chunkLocation.m_y > m_visibleRadius)
	{
		__IE_WARNING__("IEArea : out of range.\n");
		return false;
	}
	return true;
}

IE_END