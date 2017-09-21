/***********************************
* name     : IEProp.h
* creater  : cosc
* info     : every prop in scene
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP__
#define __IE_PROP__

#include "../IEAtom.h"

IE_BEGIN

/*
** 在场景中的prop的绘制和在背包中的绘制是不同的 需要进行区分
*/

typedef enum IEPropState
{
	__prop_state_pick__,		//场景中的 允许拾取的prop
	__prop_state_pack__,		//背包中的 允许使用的prop
	__prop_state_max__
};

typedef enum IEPropType
{
	__prop_type_weapon__,		//武器类prop
	__prop_type_task__,			//任务类prop
	__prop_type_material__,		//材料类prop
	__prop_type_consumable__,	//消耗类prop
	__prop_type_max__
};

class IECreature;

class __IE_DLL__ IEProp :public IEAtom
{
public:
	IEProp();
	virtual ~IEProp();
	virtual void Initialization(unsigned int propID, IEPropState propState);
	static IEProp * Create(unsigned int propID, IEPropState propState);

public:
	virtual void EquipProp() = 0;						//装备prop
	virtual void UseProp() = 0;							//使用prop
	virtual void PickProp(IECreature * creature) = 0;	//拾取prop

	void SetPropType(IEPropType propType);				//获取道具类型
	void SetPropState(IEPropState propState);			//获取道具状态
	void SetOwner(IECreature * creature);					//设定归属者
	void SetPropID(unsigned int propID);					//设定prop的ID
	unsigned int AddPropCount(unsigned int propCount);		//增加prop的数量 返回值为 还没有放进去的量 (能放入多少就放入多少)
	unsigned int AddPropCount(IEProp * prop);				//加上新的prop
	unsigned int ReducePropCount(unsigned int count);		//减少prop的数量 返回值为 还需要的prop的数量 说明数量不够 (这种情况下已经有的不会被减少)
	void DelPropAll();										//抛弃所有的Prop

	IECreature * GetOwner();				//获取归属者
	IEPropType GetPropType();				//获取道具类型
	IEPropState GetPropState();				//获取道具状态
	int GetPropID();						//获取prop的ID
	unsigned int GetPropCount();			//得到prop的数量

protected:
	virtual void ArrangeInfo();				//每次调用后 自身处理

	virtual void DrawNodeInScene(){};			//绘制场景中的prop
	virtual void DrawNodeInPack(){};			//绘制pack中的prop

private:
	void InitUnit();						//初始化自身

	void AddSelf();							//放入场景层
	void DelSelf();							//从场景层中删除出去

protected:
	IEPropState m_propState;				//当前状态
	IEPropType m_propType;					//类型
	IECreature * m_owner;					//所有者

	unsigned int m_propID;					//ID
	unsigned int m_unitID;					//unit ID
	unsigned int m_pileMax;					//堆叠上限 当该值为1的时候 即不可堆叠
	unsigned int m_propCount;				//当前堆叠计数
};

IE_END

#endif