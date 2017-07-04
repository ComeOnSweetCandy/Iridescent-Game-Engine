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
#include "IETerrain.h"

IE_BEGIN

class __IE_DLL__ IETerrainChunk :public IEChunk
{
public:
	IETerrainChunk();
	virtual ~IETerrainChunk();
	virtual void Initialization(unsigned int sideLength);
	static IETerrainChunk * Create(unsigned int sideLength);

public:
	void ResetCache();			//重置所有的block IE为0
	void FillCache();			//为了在加载不同chunk的时候能够快速加载 所有位置的block都会预先被填写满 直接更换block的ID和MODE即可
};

IE_END

#endif