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
	void SetCenterChunkLocation(int chunkLocationX, int chunkLocationY);			//设置中心chunk的位置
	void SetCenterBlockLocation(int blockLocationX, int blockLocationY);			//设置中心的block的位置

	IEChunk * GetChunk(int chunkLocationX, int chunkLocationY);						//通过chunk的位置获取chunk
	IEBlock * GetBlock(int blockLocationX, int blockLocationY);						//通过block的位置获取block

	IEContainer * GetAlters();														//获取当前所有的修改
	IEMap * GetBindedMap();															//获取绑定的地图

	void SetCurOrder(unsigned int order);											//设定当前的编号
	unsigned int GetCurOrder();														//取得编号

	//所有对于area的修改的接口
	virtual void RollbackAlter(){};													//回滚一次操作
	virtual void RollbackAllAlters(){};												//回滚所有的操作

	virtual void MouseMove(float x, float y){};										//鼠标的移动 这个时候显示ready的block
	virtual void MouseCancel(){};
	virtual void MouseClick(){};

protected:
	virtual void Visit();
	virtual void AddChild(IEBlock * block, int blockLocationX, int blockLocationY);		//添加子节点
	virtual void StanceChild(IEBlock * block, int blockLocationX, int blockLocationY);	//占位一个子节点
	virtual void RemoveChild(int blockLocationX, int blockLocationY);					//删除子节点

	virtual void LoadChunks();															//读取当前所有的chunk的数据
	virtual void LoadChunk(int blockX, int blockY);										//子类必须继承 读取指定的chunk的数据
	virtual void ClearChunks();															//清理所有chunk中的内容

	virtual IEChunk * CreateChunk();													//子类必须继承 用于创建一个新的chunk各自的实现

	void LocationTranslate(int blockLocationX, int blockLocationY, int& chunkLocationX, int& chunkLocationY, int& explicitLocationX, int& explicitLocationY);		//将block的位置转换为相应的chunk位置和内部位置
	void InitChunks();																																				//初始化chunks表

protected:
	IESceneType m_sceneType;				//类型
	int m_visibleRadius;					//可见的范围
	int m_visibleLength;					//可见的范围的一边长
	int m_visibleChunksCount;				//能最多同时显示的chunk的数目
	int m_chunkLength;						//一个chunk的边长 也就是一边有多少个block
	unsigned char m_curOrder;				//当前编号
	
	IEMap * m_map;
	IEGrid m_centerChunkLocation;			//当前中心点的chunk的位置

	IEChunkUnit ** m_chunks;				//存储所有的chunks
	IEChunkUnit *** m_chunksIndexMatrix;	//chunks的索引矩阵

	//以下数据都是编辑模式下会用到的内容
	IEContainer * m_alters;								//对于当前area的所有修改都会被记录下来
	IESprite * m_suspension;							//悬浮在鼠标上端的sprite
	IEBlock * m_choosen;								//选择了的block

	IEGrid m_mouseLocation;								//记录当前鼠标所位于的格子

	friend class IEPathAnticipate;
	friend class IEMap;
};

IE_END

#endif