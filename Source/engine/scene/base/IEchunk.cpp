#define __IE_DLL_EXPORTS__
#include "IEchunk.h"
#include "IEarea.h"

IE_BEGIN

IEChunk::IEChunk()
{
	m_blocksMatrix = NULL;
	m_sideLength = 0;
}

IEChunk::~IEChunk()
{
	if (m_blocksMatrix)
	{
		for (int index = 0; index < m_sideLength; index++)
		{
			delete[] m_blocksMatrix[index];
		}
		delete[] m_blocksMatrix;
	}
}

void IEChunk::Initialization(unsigned int sideLength)
{
	IELayer::Initialization();

	InitSideLength(sideLength);
	InitBlocksMatrix();
}

IEChunk * IEChunk::Create(unsigned int sideLength)
{
	IEChunk * object = new IEChunk();
	object->Initialization(sideLength);
	return object;
}

void IEChunk::InitSideLength(unsigned int sideLength)
{
	m_sideLength = sideLength;
}

void IEChunk::InitBlocksMatrix()
{
	m_blocksMatrix = new IEBlock **[m_sideLength];
	for (int index = 0; index < m_sideLength; index++)
	{
		m_blocksMatrix[index] = new IEBlock *[m_sideLength];
	}
	for (int mx = 0; mx < m_sideLength; mx++)
	{
		for (int my = 0; my < m_sideLength; my++)
		{
			m_blocksMatrix[mx][my] = NULL;
		}
	}
}

void IEChunk::DrawNode()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(m_sideLength, 0.0f);
	glVertex2f(m_sideLength, m_sideLength);
	glVertex2f(0.0f, m_sideLength);
	glEnd();
}

void IEChunk::AddChild(IEBlock * block, int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_sideLength || explicitLocationY >= m_sideLength || explicitLocationX < 0 || explicitLocationY < 0)
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
		if (m_blocksMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_blocksMatrix[explicitLocationX][explicitLocationY]);
			IENode::AddChild(block);
			m_blocksMatrix[explicitLocationX][explicitLocationY] = block;
			block->SetTranslate(explicitLocationX, explicitLocationY);
		}
		else
		{
			IENode::AddChild(block);
			m_blocksMatrix[explicitLocationX][explicitLocationY] = block;
			block->SetTranslate(explicitLocationX, explicitLocationY);
		}
	}
}

void IEChunk::StanceChild(IEBlock * block, int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_sideLength || explicitLocationY >= m_sideLength || explicitLocationX < 0 || explicitLocationY < 0)
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
		if (m_blocksMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_blocksMatrix[explicitLocationX][explicitLocationY]);
			m_blocksMatrix[explicitLocationX][explicitLocationY] = block;
		}
		else
		{
			m_blocksMatrix[explicitLocationX][explicitLocationY] = block;
		}
	}
}

void IEChunk::RemoveChild(int explicitLocationX, int explicitLocationY)
{
	if (explicitLocationX >= m_sideLength || explicitLocationY >= m_sideLength || explicitLocationX < 0 || explicitLocationY < 0)
	{
		__IE_WARNING__("IEChunk : out of range.\n");
		return;
	}
	else
	{
		if (m_blocksMatrix[explicitLocationX][explicitLocationY])
		{
			IENode::RemoveChild(m_blocksMatrix[explicitLocationX][explicitLocationY]);
			m_blocksMatrix[explicitLocationX][explicitLocationY] = NULL;
		}
	}
}

void IEChunk::RemoveChild(IEBlock * block)
{
	for (int mx = 0; mx < m_sideLength; mx++)
	{
		for (int my = 0; my < m_sideLength; my++)
		{
			if (m_blocksMatrix[mx][my] == block)
			{
				IENode::RemoveChild(m_blocksMatrix[mx][my]);
				m_blocksMatrix[mx][my] = NULL;
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
	if (explicitX < 0 || explicitY < 0 || explicitX >= m_sideLength || explicitY >= m_sideLength)
	{
		int blockX = m_location.m_x;
		int blockY = m_location.m_y;

		if (explicitX < 0)
		{
			blockX--;
			explicitX = m_sideLength - 1;
		}
		if (explicitY < 0)
		{
			blockY--;
			explicitY = m_sideLength - 1;
		}
		if (explicitX >= m_sideLength)
		{
			blockX++;
			explicitX = 0;
		}
		if (explicitY >= m_sideLength)
		{
			blockY++;
			explicitY = 0;
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
		return m_blocksMatrix[explicitX][explicitY];
	}
}

IEBlock *** IEChunk::GetBlocksMatrix()
{
	return m_blocksMatrix;
}

IE_END