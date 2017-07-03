#define __IE_DLL_EXPORTS__
#include "IEthingChunk.h"

IE_BEGIN

IEThingChunk::IEThingChunk()
{

}

IEThingChunk::~IEThingChunk()
{

}

void IEThingChunk::Initialization(int sideLength)
{
	IELayer::Initialization();

	InitSideLength(sideLength);
	InitThingsMatrix();
}

IEThingChunk * IEThingChunk::Create(int sideLength)
{
	IEThingChunk * chunk = new IEThingChunk();
	chunk->Initialization(sideLength);
	return chunk;
}

void IEThingChunk::AddChild(IEThing * block, int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY)
{
	m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX] = block;
	IENode::AddChild(block);
}

void IEThingChunk::StanceChild(IEThing * block, int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY)
{
	m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX] = block;
}

void IEThingChunk::EraseChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY)
{
	m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX] = NULL;
}

void IEThingChunk::RemoveChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY)
{
	m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX]->RemoveFromParent();
	m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX] = NULL;
}

void IEThingChunk::RemoveChild(IEThing * block)
{

}

IEThing * IEThingChunk::GetChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY)
{
	return m_thingsMatrix[explicitLocationX][explicitLocationY][tinyLocationY * 4 + tinyLocationX];
}

void IEThingChunk::InitThingsMatrix()
{
	m_thingsMatrix = new IEThing ***[m_chunkLength];
	for (int index = 0; index < m_chunkLength; index++)
	{
		m_thingsMatrix[index] = new IEThing **[m_chunkLength];
	}
	for (int mx = 0; mx < m_chunkLength; mx++)
	{
		for (int my = 0; my < m_chunkLength; my++)
		{
			m_thingsMatrix[mx][my] = new IEThing *[16];

			for (int mz = 0; mz < 16; mz++)
			{
				m_thingsMatrix[mx][my][mz] = NULL;
			}
		}
	}
}

void IEThingChunk::ResetThingMatrix()
{
	for (int mx = 0; mx < m_chunkLength; mx++)
	{
		for (int my = 0; my < m_chunkLength; my++)
		{
			for (int mz = 0; mz < 16; mz++)
			{
				m_thingsMatrix[mx][my][mz] = NULL;
			}
		}
	}

	RemoveAllChilds();
}

IE_END