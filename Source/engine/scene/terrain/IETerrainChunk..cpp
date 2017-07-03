#define __IE_DLL_EXPORTS__
#include "IETerrainChunk.h"

IE_BEGIN

IETerrainChunk::IETerrainChunk()
{
	m_chunksIndexMatrix = NULL;
	m_chunkLength = 0;
}

IETerrainChunk::~IETerrainChunk()
{

}

void IETerrainChunk::Initialization(int blockSize)
{
	IEChunk::Initialization(blockSize);

	FillCache();
}

IETerrainChunk * IETerrainChunk::Create(int blockSize)
{
	IETerrainChunk * object = new IETerrainChunk();
	object->Initialization(blockSize);
	return object;
}

void IETerrainChunk::FillCache()
{
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IETerrainBlock * empty = IETerrainBlock::Create(0, __terrain_none_mode__, 0);
			empty->SetDisplay(false);

			AddChild(empty, x, y);
		}
	}
}

void IETerrainChunk::ResetCache()
{
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			if (m_chunksIndexMatrix[x][y])
			{
				IETerrainBlock * block = (IETerrainBlock *)m_chunksIndexMatrix[x][y];

				block->SetTerrainID(0);
				block->SetDisplay(false);
			}
		}
	}
}

IE_END