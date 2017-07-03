/***********************************
* name     : IETerrainChuck.h
* creater  : cosc
* info     : terrain chunk
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN_CHUNK__
#define __IE_TERRAIN_CHUNK__

#include "../IEChunk.h"
#include "IETerrainBlock.h"

IE_BEGIN

class __IE_DLL__ IETerrainChunk :public IEChunk
{
public:
	IETerrainChunk();
	virtual ~IETerrainChunk();
	virtual void Initialization(int blockSize);
	static IETerrainChunk * Create(int blockSize);

public:
	void ResetCache();
	void FillCache();

private:
};

IE_END

#endif