/***********************************
* name     : IEPathChunk.h
* creater  : cosc
* info     : path block
* date     : 2017/4/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PATH_BLOCK__
#define __IE_PATH_BLOCK__

#include "../IEChunk.h"
#include "IEPath.h"

IE_BEGIN

class __IE_DLL__ IEPathChunk :public IEChunk
{
public:
	IEPathChunk();
	virtual ~IEPathChunk();
	virtual void Initialization(int& blockSize);
	static IEPathChunk * Create(int blockSize);

private:
	void ResetPathGrid();
};

IE_END

#endif