/***********************************
* name     : IEthingChunk.h
* creater  : cosc
* info     : thing chunk
* date     : 2016/12/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_CHUNK__
#define __IE_THING_CHUNK__

#include "../IEChunk.h"
#include "IEthing.h"

IE_BEGIN

class __IE_DLL__ IEThingChunk :public IEChunk
{
public:
	IEThingChunk();
	virtual ~IEThingChunk();
	virtual void Initialization(int sideLength);
	static IEThingChunk * Create(int sideLength);

public:
	virtual void AddChild(IEThing * block, int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY);
	virtual void StanceChild(IEThing * block, int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY);
	virtual void EraseChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY);
	virtual void RemoveChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY);
	virtual void RemoveChild(IEThing * block);

	IEThing * GetChild(int explicitLocationX, int explicitLocationY, int tinyLocationX, int tinyLocationY);

protected:
	void InitThingsMatrix();
	void ResetThingMatrix();

private:
	IEThing **** m_thingsMatrix;
};

IE_END

#endif