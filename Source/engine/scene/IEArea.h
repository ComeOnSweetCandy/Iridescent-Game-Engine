/***********************************
* name     : IEArea.h
* creater  : cosc
* info     : block manager area
* date     : 2016/12/11
* version  : 1.0
* remark   : none
************************************/
#ifndef __IE_AREA__
#define __IE_AREA__

#include "IEChunk.h"
#include "IEmap.h"

IE_BEGIN

typedef enum __ieSceneType
{
	__ie_scene_none__,
	__ie_scene_terrain__,
	__ie_scene_thing__,
	__ie_scene_marble__
}IESceneType;

typedef enum __ieSceneEditMode
{
	__ie_sceneEdit_touch__,
	__ie_sceneEdit_brush__,
	__ie_sceneEdit_choose__
}IESceneEditMode;

typedef struct __ieChunkBlock
{
	IEGrid _ChunkLocation;
	IEChunk * _Chunk;
	bool _Using;
}IEChunkUnit;

class __IE_DLL__ IEArea :public IELayer
{
public:
	IEArea();
	virtual ~IEArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IEArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	void SetCenterChunkLocation(int chunkLocationX, int chunkLocationY);			//��������chunk��λ��
	void SetCenterBlockLocation(int blockLocationX, int blockLocationY);			//�������ĵ�block��λ��

	IEChunk * GetChunk(int chunkLocationX, int chunkLocationY);						//ͨ��chunk��λ�û�ȡchunk
	IEBlock * GetBlock(int blockLocationX, int blockLocationY);						//ͨ��block��λ�û�ȡblock

	IEContainer * GetAlters();														//��ȡ��ǰ���е��޸�
	IEMap * GetBindedMap();															//��ȡ�󶨵ĵ�ͼ

	void SetCurOrder(unsigned int order);											//�趨��ǰ�ı��
	unsigned int GetCurOrder();														//ȡ�ñ��

	virtual void RollbackAlter(){};													//�ع�һ�β���
	virtual void RollbackAllAlters(){};												//�ع����еĲ���

	virtual void MouseMove(float x, float y);										//�����ƶ� ���ʱ����ʾready��block
	virtual void MouseChoose(){};
	virtual void MouseCancel(){};
	virtual void MouseClick(){};

protected:
	virtual void Visit();
	virtual void AddChild(IEBlock * block, int blockLocationX, int blockLocationY);		//����ӽڵ�
	virtual void StanceChild(IEBlock * block, int blockLocationX, int blockLocationY);	//ռλһ���ӽڵ�
	virtual void RemoveChild(int blockLocationX, int blockLocationY);					//ɾ���ӽڵ�

	virtual void LoadChunks();															//��ȡ��ǰ���е�chunk������
	virtual void LoadChunk(int blockX, int blockY);										//�������̳� ��ȡָ����chunk������
	virtual void ClearChunks();															//��������chunk�е�����

	virtual IEChunk * CreateChunk();													//�������̳� ���ڴ���һ���µ�chunk���Ե�ʵ��

	void LocationTranslate(int blockLocationX, int blockLocationY, int& chunkLocationX, int& chunkLocationY, int& explicitLocationX, int& explicitLocationY);		//��block��λ��ת��Ϊ��Ӧ��chunkλ�ú��ڲ�λ��
	void InitChunks();																																				//��ʼ��chunks��

protected:
	IESceneType m_sceneType;				//����
	int m_visibleRadius;					//�ɼ��ķ�Χ
	int m_visibleLength;					//�ɼ��ķ�Χ��һ�߳�
	int m_visibleChunksCount;				//�����ͬʱ��ʾ��chunk����Ŀ
	int m_chunkLength;						//һ��chunk�ı߳� Ҳ����һ���ж��ٸ�block
	unsigned char m_curOrder;				//��ǰ���
	
	IEMap * m_map;
	IEGrid m_centerChunkLocation;			//��ǰ���ĵ��chunk��λ��

	IEChunkUnit ** m_chunks;				//�洢���е�chunks
	IEChunkUnit *** m_chunksIndexMatrix;	//chunks����������

	//�������ݶ��Ǳ༭ģʽ�»��õ�������
	IEContainer * m_alters;								//���ڵ�ǰarea�������޸Ķ��ᱻ��¼����
	static unsigned char m_edit_active_scene;			//��ǰ�ļ���ĳ����ı�� 0Ϊδѡ���κγ���
	static unsigned char m_edit_mode;					//��ǰ�ĳ����޸�ģʽ 0��� 1��ˢ 2ѡ��ģʽ
	IESprite * m_moveThing;								//����������϶˵�sprite

	friend class IEPathAnticipate;
	friend class IEMap;
};

IE_END

#endif