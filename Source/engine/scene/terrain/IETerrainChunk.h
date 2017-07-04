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
	void ResetCache();			//�������е�block IEΪ0
	void FillCache();			//Ϊ���ڼ��ز�ͬchunk��ʱ���ܹ����ټ��� ����λ�õ�block����Ԥ�ȱ���д�� ֱ�Ӹ���block��ID��MODE����
};

IE_END

#endif