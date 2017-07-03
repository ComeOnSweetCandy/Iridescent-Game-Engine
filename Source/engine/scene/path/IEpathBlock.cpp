#define __IE_DLL_EXPORTS__
#include "IEpathBlock.h"

IE_BEGIN

IEPathBlock::IEPathBlock()
{
	m_chunksIndexMatrix = NULL;
	m_chunkLength = 0;
}

IEPathBlock::~IEPathBlock()
{
	
}

void IEPathBlock::Initialization(int & blockSize)
{
	IEChunk::Initialization(blockSize);

	ResetPathGrid();
}

IEPathBlock * IEPathBlock::Create(int blockSize)
{
	IEPathBlock * object = new IEPathBlock();
	object->Initialization(blockSize);
	return object;
}

void IEPathBlock::ResetPathGrid()
{
	for (int x = 0; x < m_chunkLength; x++)
	{
		for (int y = 0; y < m_chunkLength; y++)
		{
			IEPathGrid * grid = IEPathGrid::Create();
			grid->SetGridGrid(x, y);

			AddChild(grid, x, y);
		}
	}
}

IE_END