/***********************************
* name     : IEThing.h
* creater  : cosc
* info     : base ting
* date     : 2017/3/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING__
#define __IE_THING__

#include "../IEBlock.h"

#include "../../trigger/IEtrigger.h"

IE_BEGIN

class __IE_DLL__ IEThing :public IEBlock
{
public:
	IEThing();
	virtual ~IEThing();
	virtual void Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);
	static IEThing * Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder);

public:
	void SetThingType(unsigned int thingType);
	unsigned int GetThingType();
	void SetThingID(unsigned int thingID);
	unsigned int GetThingID();
	void SetOrder(unsigned int order);
	unsigned int GetOrder();
	void SetRelatedOrder(unsigned int relatedCreatedOrder);
	unsigned int GetRelatedOrder();
	void SetExpress(bool express);
	bool GetExpress();
	void SetLocations(int blockLocationX, int blockLocationY, int tinyLocationX, int tinyLocationY);	//让thing记录其自身的的位置参数
	int * GetLocations();																				//获取thing的位置参数

	virtual void SwitchStateTo(const char * stateName);													//转换一种状态
	virtual void CallFinal();																			//当获取完了所有的信息后 进行一些结尾的计算
	virtual void CheckAround(bool active);																//对周围进行检查 active代表 是自发性检查 还是周围元素驱使下的检查 主要防止递归调用

private:
	void LoadXML();			//从XML中读取个人信息
	void LoadLUA();			//加载脚本文件

protected:
	unsigned int m_thingType;				//thing的类型
	unsigned int m_thingID;					//thing的ID
	unsigned int m_order;					//该thing的序号
	unsigned int m_relatedOrder;			//关联的物体的序号
	bool m_express;							//它所占格子位置是否已经完全表达
	int m_locations[4];						//记录该thing的位置和tiny精确位置

	unsigned char m_maxState;				//最大的状态值
	unsigned char m_curState;				//当前的状态值
};

IE_END

#endif