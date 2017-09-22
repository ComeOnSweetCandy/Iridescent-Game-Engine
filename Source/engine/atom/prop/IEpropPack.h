/***********************************
* name     : IEPropPack.h
* creater  : cosc
* info     : bag
* date     : 2017/3/31
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_PACK__
#define __IE_PROP_PACK__

#include "IEProp.h"

IE_BEGIN

class IESlot;

class __IE_DLL__ IEPropPack:public IEObject
{
public:
	IEPropPack();
	virtual ~IEPropPack();
	virtual void Initialization(IEArmer * creature, unsigned int packCapacity);
	static IEPropPack * Create(IEArmer * creature, unsigned int packCapacity);

public:
	virtual void UpdateUI();								//更新绑定的UI
	void ListProp();										//列举背包里的所有物品

	void AddProp(IEProp * prop);							//放入prop
	void DropProp(unsigned int packIndex);					//丢弃prop
	void DropProp(IEProp * prop);							//丢弃prop
	void UseProp(unsigned int packIndex);					//使用prop

	void ChangePropIndex(IEProp * prop1, IEProp * prop2);	//更换两个prop位置
	int GetPropIndex(IEProp * prop);						//获取prop的位置

private:
	void SetSlot(IESlot * shortCut);					//???

	void SetPackCapacity(unsigned int packCapacity);	//设定pack容量
	void SetPackOwner(IEArmer * creature);				//设定pack的拥有着

	unsigned int GetPackCapacity();						//获取pack容量
	IEArmer * GetPackOwner();							//获取pack拥有着

public:
	unsigned int m_packCapacity;						//pack最大容量
	IEProp ** m_props;									//pack中所有的prop
	IEArmer * m_owner;									//拥有着

	IESlot * m_slot;
};

IE_END

#endif