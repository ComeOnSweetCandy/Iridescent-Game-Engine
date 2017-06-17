#define __IE_DLL_EXPORTS__
#include "IEterrainBlock.h"

IE_BEGIN

IETerrainBlock::IETerrainBlock()
{
	m_blocksMatrix = NULL;
	m_sideLength = 0;
}

IETerrainBlock::~IETerrainBlock()
{

}

void IETerrainBlock::Initialization(int blockSize)
{
	IEChunk::Initialization(blockSize);

	FillCache();
}

IETerrainBlock * IETerrainBlock::Create(int blockSize)
{
	IETerrainBlock * object = new IETerrainBlock();
	object->Initialization(blockSize);
	return object;
}

void IETerrainBlock::FillCache()
{
	for (int x = 0; x < m_sideLength; x++)
	{
		for (int y = 0; y < m_sideLength; y++)
		{
			IETerrainGrid * empty = IETerrainGrid::Create(0, __terrain_none_mode__, 0);
			empty->SetDisplay(false);

			AddChild(empty, x, y);
		}
	}
}

void IETerrainBlock::ResetCache()
{
	for (int x = 0; x < m_sideLength; x++)
	{
		for (int y = 0; y < m_sideLength; y++)
		{
			if (m_blocksMatrix[x][y])
			{
				IETerrainGrid * block = (IETerrainGrid *)m_blocksMatrix[x][y];

				block->SetTerrainID(0);
				block->SetDisplay(false);
			}
		}
	}
}

IE_END