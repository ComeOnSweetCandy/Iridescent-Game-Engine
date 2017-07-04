#define __IE_DLL_EXPORTS__
#include "IEChunk.h"
#include "IEArea.h"

IE_BEGIN

IEChunk::IEChunk()
{
	m_chunksIndexMatrix = NULL;
	m_chunkLength = 0;
}

IEChunk::~IEChunk()
{
	if (m_chunksIndexMatrix)
	{
		for (int index = 0; index < m_chunkLength; index++)
		{
			delete[] m_chunksIndexMatrix[index];
		}
		delete[] m_chunksIndexMatrix;
	}
}

void IEChunk::Initialization(unsigned int sideLength)
{
	IELayer::Initialization();

	IEChunk::InitSideLength(sideLength);
	IEChunk::InitBlocksMatrix();
}

IEChunk * IEChunk::Create(unsigned int sideLength)
{
	IEChunk * object = new IEChunk();
	object->Initialization(sideLength);
	return object;
}

void IEChunk::InitSideLength(unsigned int sideLength)
{
	m_chunkLength = sideLength;
}

void IEChunk::InitBlocksMatrix()
{
	m_chunksIndexMatrix = new IEBlock **[m_chunkLength];
	for (int index = 0; index < m_chunkLength; index++)
	{
		m_chunksIndexMatrix[index] = new IEBlock *[m_chunkLength];
	}
	for (int mx = 0; mx < m_chunkLength; mx++)
	{
		for (int my = 0; my < m_chunkLength; my++)
		{
			m_chunksIndexMatrix[mx][my] = NULL;
		}
	}
}

void IEChunk::DrawNode()
{
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glBegin(GL_LINE_LOOP);
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(m_chunkLength, 0.0f);
	//glVertex2f(m_chunkLength, m_chunkLength);
	//glVertex2f(0.0f, m_chunkLength);
	//glEnd();
}

void IEChunk::AddChild(IEBlock * block, int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_chunkLength || explicitLocationY >= m_chunkLength || explicitLocationX < 0 || explicitLocationY < 0)
	{
		__IE_WARNING__("IEChunk : out of range.\n");
		return;
	}
	else
	{
		if (block == NULL)
		{
			__IE_WARNING__("IEChunk : the block is empty which was set to block.\n");
			return;
		}
		if (m_chunksIndexMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_chunksIndexMatrix[explicitLocationX][explicitLocationY]);
			IENode::AddChild(block);
			m_chunksIndexMatrix[explicitLocationX][explicitLocationY] = block;
			block->SetTranslate(explicitLocationX, explicitLocationY);
		}
		else
		{
			IENode::AddChild(block);
			m_chunksIndexMatrix[explicitLocationX][explicitLocationY] = block;
			block->SetTranslate(explicitLocationX, explicitLocationY);
		}
	}
}

void IEChunk::StanceChild(IEBlock * block, int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_chunkLength || explicitLocationY >= m_chunkLength || explicitLocationX < 0 || explicitLocationY < 0)
	{
		__IE_WARNING__("IEChunk : out of range.\n");
		return;
	}
	else
	{
		if (block == NULL)
		{
			__IE_WARNING__("IEChunk : the block is empty which was set to block.\n");
			return;
		}
		if (m_chunksIndexMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_chunksIndexMatrix[explicitLocationX][explicitLocationY]);
			m_chunksIndexMatrix[explicitLocationX][explicitLocationY] = block;
		}
		else
		{
			m_chunksIndexMatrix[explicitLocationX][explicitLocationY] = block;
		}
	}
}

void IEChunk::RemoveChild(int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_chunkLength || explicitLocationY >= m_chunkLength || explicitLocationX < 0 || explicitLocationY < 0)
	{
		__IE_WARNING__("IEChunk : out of range.\n");
		return;
	}
	else
	{
		if (m_chunksIndexMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_chunksIndexMatrix[explicitLocationX][explicitLocationY]);
			m_chunksIndexMatrix[explicitLocationX][explicitLocationY] = NULL;
		}
	}
}

void IEChunk::RemoveChild(IEBlock * block)
{
	for (int mx = 0; mx < m_chunkLength; mx++)
	{
		for (int my = 0; my < m_chunkLength; my++)
		{
			if (m_chunksIndexMatrix[mx][my] == block)
			{
				IENode::RemoveChild(m_chunksIndexMatrix[mx][my]);
				m_chunksIndexMatrix[mx][my] = NULL;
				return;
			}
		}
	}
}

void IEChunk::BindArea(IEArea * area)
{
	m_area = area;
}

IEArea * IEChunk::GetBindedArea()
{
	return m_area;
}

void IEChunk::SetLocation(int x, int y)
{
	m_location = IEGrid(x, y);
}

const IEGrid & IEChunk::GetLocation()
{
	return m_location;
}

IEBlock * IEChunk::GetBlock(int explicitX, int explicitY)
{
	if (explicitX < 0 || explicitY < 0 || explicitX >= m_chunkLength || explicitY >= m_chunkLength)
	{
		int blockX = m_location.m_x;
		int blockY = m_location.m_y;

		while (explicitX < 0)
		{
			blockX--;
			explicitX = explicitX + m_chunkLength;
		}
		while (explicitY < 0)
		{
			blockY--;
			explicitY = explicitX + m_chunkLength;
		}
		while (explicitX >= m_chunkLength)
		{
			blockX++;
			explicitX = explicitX - m_chunkLength;
		}
		while (explicitY >= m_chunkLength)
		{
			blockY++;
			explicitY = explicitY - m_chunkLength;
		}

		IEChunk * chunk = m_area->GetChunk(blockX, blockY);
		if (chunk)
		{
			return chunk->GetBlock(explicitX, explicitY);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return m_chunksIndexMatrix[explicitX][explicitY];
	}
}

IEBlock *** IEChunk::GetBlocksMatrix()
{
	return m_chunksIndexMatrix;
}

IE_END