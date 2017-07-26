#define __IE_DLL_EXPORTS__
#include "IEPathChunk.h"

IE_BEGIN

IEPathChunk::IEPathChunk()
{
	m_chunksIndexMatrix = NULL;
	m_chunkLength = 0;
}

IEPathChunk::~IEPathChunk()
{
	
}

void IEPathChunk::Initialization(int& blockSize)
{
	IEChunk::Initialization(blockSize);

	ResetPathGrid();
}

IEPathChunk * IEPathChunk::Create(int blockSize)
{
	IEPathChunk * object = new IEPathChunk();
	object->Initialization(blockSize);
	return object;
}

void IEPathChunk::ResetPathGrid()
{
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IEPath * grid = IEPath::Create();
			grid->SetGridGrid(x, y);

			AddChild(grid, x, y);
		}
	}
}

IE_END