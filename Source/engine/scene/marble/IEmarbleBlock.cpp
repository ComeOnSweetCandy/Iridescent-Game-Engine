#define __IE_DLL_EXPORTS__
#include "IEmarbleBlock.h"

IE_BEGIN

IEMarbleBlock::IEMarbleBlock()
{

}

IEMarbleBlock::~IEMarbleBlock()
{

}

void IEMarbleBlock::Initialization(int & blockSize)
{
	IEChunk::Initialization(blockSize);
}

IEMarbleBlock * IEMarbleBlock::Create(int blockSize)
{
	IEMarbleBlock * object = new IEMarbleBlock();
	object->Initialization(blockSize);
	return object;
}

IE_END