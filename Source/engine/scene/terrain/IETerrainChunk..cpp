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

void IETerrainChunk::Initialization(unsigned int sideLength)
{
	IEChunk::Initialization(sideLength);

	FillCache();
}

IETerrainChunk * IETerrainChunk::Create(unsigned int sideLength)
{
	IETerrainChunk * object = new IETerrainChunk();
	object->Initialization(sideLength);
	return object;
}

void IETerrainChunk::FillCache()
{
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IETerrain * empty = IETerrain::Create(0, __terrain_none_mode__, 0);
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
				IETerrain * block = (IETerrain *)m_chunksIndexMatrix[x][y];
				block->SetTerrainID(0);
			}
		}
	}
}

IE_END