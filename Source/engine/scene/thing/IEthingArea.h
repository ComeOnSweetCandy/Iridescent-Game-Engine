/***********************************
* name     : IEThingArea.h
* creater  : cosc
* info     : thing area
* date     : 2016/12/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_AREA__
#define __IE_THING_AREA__

#include "../IEArea.h"
#include "IEthingChunk.h"
#include "IEThingList.h"

IE_BEGIN

#define __IE_THING_ALTER_OPERA_ADD__ 255
#define __IE_THING_ALTER_OPERA_DEL__ 1
#define __IE_THING_ALTER_OPERA_BIN__ 2
#define __IE_THING_ALTER_OPERA_BED__ 3

class IEThingAlter:public IEObject
{
public:
	int _X;
	int _Y;
	unsigned char _TinyX;
	unsigned char _TinyY;
	unsigned int _ThingID;
	unsigned int _Order;
	unsigned int _ExtraOrder;
	unsigned char _OperaType;
};

class __IE_DLL__ IEThingArea :public IEArea
{
public:
	IEThingArea();
	virtual ~IEThingArea();
	virtual void Initialization(IEMap * map, int visibleRadius, int sideLength);
	static IEThingArea * Create(IEMap * map, int visibleRadius, int sideLength);

public:
	//�����ڱ༭ģʽ��
	virtual IEThing * AddChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	virtual void RemoveChild();
	IEThing * LoadChild(unsigned m_thingID, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);



	IEThing * ChooseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);			//ѡ��һ��child
	//virtual void AddChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);		//���һ���µ�child
	//virtual void LoadChilds(IEThingSerialization * blocksInfo, int chunkLocationX, int chunkLocationY);					//��ȡ��ͼ�ļ��е�����

	void SetReadyThing(unsigned int thingID);															//�趨׼����thing ID
	virtual void MouseMove(float x, float y);															//�����ƶ�
	virtual void MouseCancel();																			//�����Ҽ�ȡ��
	virtual void MouseClick();																			//��ready���µ�һ�ε��
	virtual void MouseBrush();																			//���ˢ��

	virtual void RollbackControll();
	virtual void RollbackAllControlls();





	//��ȡģʽ��
	void LoadChild(int blockX, int blockY, IEThingBlockFormat * alters);

	//���ýӿ�
	IEThing * FindThingByOrder(unsigned int thingOrder);

private:
	void AddThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};
	void HoldThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};
	void EraseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};
	void RemoveThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};

	virtual IEChunk * CreateChunk();

	virtual void Visit();

	IEThing * CreateThing(unsigned thingID);

	virtual void LoadChunk(int blockX, int blockY);

	bool AllowChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);		//�Ƿ�����ǰ���������

private:
	IEAdorningInfo * m_thingsInfo;
	IEThingAlter * m_alter;

	unsigned int m_readyThingID;
	unsigned int m_choosenThingOrder;

	//IEGrid m_mouseLocation;
	IEGrid m_mouseTinyLocation;
	bool m_regularization;			//����µ�thingʱ�Ƿ��ǹ�����

	friend class IEMap;
};

IE_END

#endif