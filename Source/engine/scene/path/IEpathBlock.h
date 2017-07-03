/***********************************
* name     : IEpathBlock.h
* creater  : cosc
* info     : path block
* date     : 2017/4/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PATH_BLOCK__
#define __IE_PATH_BLOCK__

#include "../IEChunk.h"
#include "IEpathGrid.h"

IE_BEGIN

class __IE_DLL__ IEPathBlock :public IEChunk
{
public:
	IEPathBlock();
	virtual ~IEPathBlock();
	virtual void Initialization(int & blockSize);
	static IEPathBlock * Create(int blockSize);

private:
	void ResetPathGrid();
};

IE_END

#endif