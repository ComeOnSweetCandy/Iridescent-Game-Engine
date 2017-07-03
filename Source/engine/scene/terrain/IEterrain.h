/***********************************
* name     : IETerrain.h
* creater  : cosc
* info     : terrain
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN__
#define __IE_TERRAIN__

#include "../IEArea.h"
#include "IETerrainChunk.h"
#include "IETerrainsInfoManager.h"

IE_BEGIN

typedef struct ieTerrainAlterInfo
{
	unsigned int _TerrainID;
	IETerrainMode _TerrainMode;
	unsigned int _Order;
}IETerrainAlterInfo;

class IETerrainAlter:public IEObject
{
public:
	int _X;
	int _Y;

	IETerrainAlterInfo _TerrainInfo;
	IETerrainAlterInfo _TerrainInfoOld;
};

class __IE_DLL__ IETerrain :public IEArea
{
public:
	IETerrain();
	virtual ~IETerrain();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IETerrain * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual void AddChild(int blockLocationX, int blockLocationY);
	virtual void RemoveChild(int blockLocationX, int blockLocationY);

	virtual void LoadChilds(IETerrainBlockFormat * blocks, int chunkLocationX, int chunkLocationY);


	virtual void RollbackAlter();													//�ع�һ�β���
	virtual void RollbackAllAlters();												//�ع����еĲ���

	void SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode);		//�趨׼����terrain		
	virtual void MouseMove(float x, float y);										//�����ƶ�
	virtual void MouseChoose();
	virtual void MouseCancel();
	virtual void MouseClick();

private:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

	void LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);
	void LoadNone(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);

	void AddBody(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);

private:
	IETerrainInfo * m_terrainsInfo;
	IETerrainAlter * m_alter;

	unsigned int m_choosedTerrainOrder;
	unsigned int m_readyTerrainID;
	IETerrainMode m_readyTerrainMode;

	//�����ַ���ƴ���������Ŀ���
	char * m_loadString[4];
	char stringBody[16];
	char stringBorder[16];
	char stringNumber[16];
	char stringPNG[16];

	friend class IEMap;
};

IE_END

#endif