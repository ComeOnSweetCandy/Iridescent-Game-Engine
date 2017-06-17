/***********************************
* name     : IEterrainBlock.h
* creater  : cosc
* info     : terrain block
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN_BLOCK__
#define __IE_TERRAIN_BLOCK__

#include "../base/IEchunk.h"
#include "IEterrainGrid.h"

IE_BEGIN

class __IE_DLL__ IETerrainBlock :public IEChunk
{
public:
	IETerrainBlock();
	virtual ~IETerrainBlock();
	virtual void Initialization(int blockSize);
	static IETerrainBlock * Create(int blockSize);

public:
	void ResetCache();
	void FillCache();

private:
};

IE_END

#endif