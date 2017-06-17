/***********************************
* name     : IEchunk.h
* creater  : cosc
* info     : big block = chunk
* date     : 2016/12/12
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CHUNK__
#define __IE_CHUNK__

#include "../../../core/IElayer.h"
#include "IEblock.h"

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
	IEBlock * GetBlock(int explicitX, int explicitY);	//获取block
	IEBlock *** GetBlocksMatrix();						//获取block矩阵

	void BindArea(IEArea * area);			//设定绑定的area
	IEArea * GetBindedArea();				//获取绑定的area

	void SetLocation(int x, int y);			//设置chunk的定位
	const IEGrid& GetLocation();			//得到chunk定位

protected:
	virtual void DrawNode();

	void InitSideLength(unsigned int sideLength);
	void InitBlocksMatrix();

protected:
	IEArea * m_area;
	int m_sideLength;
	IEGrid m_location;
	IEBlock *** m_blocksMatrix;

	friend class IEArea;
};

IE_END

#endif