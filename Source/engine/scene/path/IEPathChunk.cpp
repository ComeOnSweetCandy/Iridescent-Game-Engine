#define __IE_DLL_EXPORTS__
#include "IEPathChunk.h"

IE_BEGIN

IEPathChunk::IEPathChunk()
{
	m_tunnels = NULL;
	m_chunksIndexMatrix = NULL;
	m_chunkLength = 0;
}

IEPathChunk::~IEPathChunk()
{
	free(m_tunnels);
}

void IEPathChunk::Initialization(int& blockSize)
{
	IEChunk::Initialization(blockSize);

	m_tunnels = (unsigned char ***)malloc(sizeof(unsigned char)* m_chunkLength * m_chunkLength * 16);

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
	//m_tunnels = new unsigned char **[m_chunkLength];
	//for (int x = 0; x < m_chunkLength; x++)
	//{
	//	m_tunnels[x] = new unsigned char *[m_chunkLength];
	//}

	//for (int x = 0; x < m_chunkLength; x++)
	//{
	//	for (int y = 0; y < m_chunkLength; y++)
	//	{
	//		m_tunnels[x][y] = new unsigned char[16];
	//	}
	//}

	memset(m_tunnels, 0xFF, m_chunkLength * m_chunkLength * 16);
	
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