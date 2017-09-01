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
#include "IETerrainList.h"

IE_BEGIN

class IETerrainAlter:public IEObject
{
public:
	IETerrainAlter(){};
	~IETerrainAlter()
	{ 
		__IE_DELETE__(_CurtTerrainInfoSerialization);
		__IE_DELETE__(_PastTerrainInfoSerialization);
	}

public:
	unsigned int _AlterOrder;
	int _X;
	int _Y;
	int _ChunkX;
	int _ChunkY;

	IETerrainSerialization * _CurtTerrainInfoSerialization;
	IETerrainSerialization * _PastTerrainInfoSerialization;
};

class __IE_DLL__ IETerrainArea :public IEArea
{
public:
	IETerrainArea();
	virtual ~IETerrainArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IETerrainArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	virtual void AddChild(int blockLocationX, int blockLocationY);											//���һ���µ�child
	virtual void ChooseChild(int blockLocationX, int blockLocationY);										//ѡ��һ��child
	virtual void LoadChilds(IETerrainSerialization * blocksInfo, int chunkLocationX, int chunkLocationY);	//��ȡ��ͼ�ļ��е�����
	virtual void RemoveChild(int locationX, int locationY);

	virtual void SetReadyTerrain(unsigned int terrainID, IETerrainMode terrainMode);					//�趨׼����terrain
	virtual void MouseMove(float x, float y);															//�����ƶ�
	virtual void MouseCancel();																			//�����Ҽ�ȡ��
	virtual void MouseClick();																			//��ready���µ�һ�ε��
	virtual void MouseBrush();																			//���ˢ��

	virtual void RollbackAlter();																		//�ع�һ�β���
	virtual void RollbackAllAlters();																	//�ع����еĲ���

protected:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

private:
	//ͨ�����ĸ���ʽ������ index���������
	void ChangeNone(int blockLocationX, int blockLocationY);
	void ChangeBody(int blockLocationX, int blockLocationY);
	void ChangeBevel(int blockLocationX, int blockLocationY);
	void ChangePiece(int blockLocationX, int blockLocationY);

	void ReserializatioRound(int blockLocationX, int blockLocationY);									//һ��body�޸� �������л���Χ��border��ֵ

private:
	IETerrainEntry * m_terrainsInfo;
	IETerrainAlter * m_alter;

	unsigned int m_choosedTerrainOrder;
	unsigned int m_readyTerrainID;
	IETerrainMode m_readyTerrainMode;

	friend class IEMap;
};

IE_END

#endif