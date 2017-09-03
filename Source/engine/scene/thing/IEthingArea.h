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
	virtual IEThing * AddChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);					//���һ���µ�thing
	virtual IEThing * ChooseChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);				//ѡ��һ���Ѿ����ڵ�thing
	IEThing * GetThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);							//ѡȡһ��λ�ã��õ���thing
	IEThing * LoadChild(unsigned m_thingID, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);	//��ȡ��ͼ�е�things
	void LoadChilds(int blockX, int blockY, IEThingBlockFormat * alters);																//��ȡ��ͼ�е�things
	virtual void RemoveChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);					//�Ƴ�һ��thing

	void SetReadyThing(unsigned int thingID);															//�趨׼����thing ID
	virtual void MouseMove(float x, float y);															//�����ƶ�
	virtual void MouseCancel();																			//�����Ҽ�ȡ��
	virtual void MouseClick();																			//��ready���µ�һ�ε��
	virtual void MouseBrush();																			//���ˢ��

	virtual void RollbackControll();																	//�ع�һ�β���
	virtual void RollbackAllControlls();																//�ع����еĲ���


protected:
	virtual IEChunk * CreateChunk();
	virtual void LoadChunk(int blockX, int blockY);

private:
	void AddThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);				//��thing��ӵ���ǰ�����У���Ӧ��chunk��
	void HoldThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);			
	void EraseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};
	void RemoveThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY){};

	bool AllowChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);		//�Ƿ�����ǰ���������
	IEThing * FindThingByOrder(unsigned int thingOrder);															//ͨ��thingOrder�ҵ�thing

private:
	IEThingEntry * m_entrys;
	IEThingAlter * m_alter;

	unsigned int m_readyThingID;
	unsigned int m_choosenThingOrder;

	bool m_regularization;			//����µ�thingʱ�Ƿ��ǹ�����

	friend class IEMap;
};

IE_END

#endif