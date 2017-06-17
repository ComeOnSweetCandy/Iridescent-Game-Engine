/***********************************
* name     : IEthingArea.h
* creater  : cosc
* info     : thing area
* date     : 2016/12/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_AREA__
#define __IE_THING_AREA__

#include "../base/IEarea.h"
#include "IEthingChunk.h"
#include "IEthingsInfoManager.h"

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
	virtual void Initialization(IEMap * map, int halfViewBlocks, int blockSize);
	static IEThingArea * Create(IEMap * map, int halfViewBlocks, int blockSize);

public:
	//仅限于编辑模式下
	virtual IEThing * AddChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	virtual void RemoveChild();
	IEThing * LoadChild(unsigned m_thingID, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	IEThing * ChooseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);

	virtual void RollbackControll();
	virtual void RollbackAllControlls();

	void SetReadyThing(unsigned int thingID);
	void MouseSuspension(float positionX, float positionY);
	void MouseLButtonTouch();
	void MouseRButtonTouch();

	//读取模式下
	void LoadChild(int blockX, int blockY, IEThingBlockFormat * alters);

	//公用接口
	IEThing * FindThingByOrder(unsigned int thingOrder);

private:
	void AddThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	void HoldThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	void EraseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);
	void RemoveThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);

	virtual IEChunk * CreateChunk();

	virtual void Visit();

	IEThing * CreateThing(unsigned thingID);

	virtual void LoadChunk(int blockX, int blockY);

	bool AllowChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY);		//是否允许当前的子类插入

private:
	IEAdorningInfo * m_thingsInfo;
	IEThingAlter * m_thingAlter;

	unsigned int m_readyThingID;
	unsigned int m_choosenThingOrder;

	IESprite * m_suspensionThing;

	IEGrid m_mouseLocation;
	IEGrid m_mouseTinyLocation;

	friend class IEMap;
};

IE_END

#endif