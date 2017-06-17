/***********************************
* name     : IEmarbleBlock.h
* creater  : cosc
* info     : marble block
* date     : 2017/5/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_MARBLE_BLOCK__
#define __IE_MARBLE_BLOCK__

#include "../base/IEchunk.h"
#include "IEmarbleGrid.h"

IE_BEGIN

class __IE_DLL__ IEMarbleBlock :public IEChunk
{
public:
	IEMarbleBlock();
	virtual ~IEMarbleBlock();
	virtual void Initialization(int & blockSize);
	static IEMarbleBlock * Create(int blockSize);
};

IE_END

#endif