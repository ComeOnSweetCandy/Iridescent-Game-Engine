/***********************************
* name     : IEChunk.h
* creater  : cosc
* info     : chunk
* date     : 2016/12/12
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CHUNK__
#define __IE_CHUNK__

#include "../../core/IElayer.h"
#include "IEBlock.h"

IE_BEGIN

class IEArea;

class __IE_DLL__ IEChunk:public IELayer
{
public:
	IEChunk();
	virtual ~IEChunk();
	virtual void Initialization(unsigned int sideLength);
	static IEChunk * Create(unsigned int sideLength);

public:
	virtual void AddChild(IEBlock * block, int explicitLocationX, int explicitLocationY);
	virtual void StanceChild(IEBlock * block, int explicitLocationX, int explicitLocationY);
	virtual void RemoveChild(int explicitLocationX, int explicitLocationY);
	virtual void RemoveChild(IEBlock * block);

public:
	IEBlock * GetBlock(int explicitX, int explicitY);	//��ȡblock
	IEBlock *** GetBlocksMatrix();						//��ȡblock����

	void BindArea(IEArea * area);			//�趨�󶨵�area
	IEArea * GetBindedArea();				//��ȡ�󶨵�area

	void SetLocation(int x, int y);			//����chunk�Ķ�λ
	const IEGrid& GetLocation();			//�õ�chunk��λ

protected:
	virtual void DrawNode();

	void InitSideLength(unsigned int sideLength);
	void InitBlocksMatrix();

protected:
	IEArea * m_area;
	int m_chunkLength;
	IEGrid m_location;
	IEBlock *** m_chunksIndexMatrix;

	friend class IEArea;
};

IE_END

#endif