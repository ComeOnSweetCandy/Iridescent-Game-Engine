/***********************************
* name     : IETerrainArea.h
* creater  : cosc
* info     : terrain area
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TERRAIN_AREA__
#define __IE_TERRAIN_AREA__

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

	IETerrainAlterInfo _Terrain;
	IETerrainAlterInfo _TerrainPast;
};

class __IE_DLL__ IETerrainArea :public IEArea
{
public:
	IETerrainArea();
	virtual ~IETerrainArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IETerrainArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual void AddChild(int blockLocationX, int blockLocationY);										//���һ���µ�child
	virtual void LoadChilds(IETerrainBlockFormat * blocks, int chunkLocationX, int chunkLocationY);		//���һ�δ��ݹ��������ٵ����ݿ���

	virtual void MouseMove(float x, float y);															//�����ƶ�
	virtual void MouseCancel();																			//�����Ҽ�ȡ��
	virtual void MouseClick();																			//��ready���µ�һ�ε��
	virtual void RollbackAlter();																		//�ع�һ�β���
	virtual void RollbackAllAlters();																	//�ع����еĲ���
	virtual void SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode);					//�趨׼����terrain

private:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

	void LoadBody(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);
	void LoadNone(IETerrainChunk * chunk, int explicitGridPositionX, int explicitGridPositionY, unsigned int terrainID, unsigned int createdOrder);

	//void AddBody(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY){};
	void ApplyBevel(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyPiece(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);
	void ApplyNone(unsigned int terrainID, IETerrainMode terrainMODE, unsigned int createdOrder, int blockLocationX, int blockLocationY);

	//ͨ�����ĸ���ʽ������ index���������
	void ChangeNone(int blockLocationX, int blockLocationY);
	void ChangeBody(int blockLocationX, int blockLocationY);
	void ChangeBevel(int blockLocationX, int blockLocationY) {};
	void ChangePiece(int blockLocationX, int blockLocationY) {};

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