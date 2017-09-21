/***********************************
* name     : IEpropPack.h
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
	virtual void Initialization(IECreature * creature, unsigned int packCapacity);
	static IEPropPack * Create(IECreature * creature, unsigned int packCapacity);

public:
	virtual void UpdateUI();							//更新绑定的UI

	void AddProp(IEProp * prop);						//放入prop
	void DropProp(unsigned int packIndex);				//丢弃prop
	void UseProp(unsigned int packIndex);				//使用prop

private:
	void SetSlot(IESlot * shortCut);					//???

	void SetPackCapacity(unsigned int packCapacity);	//设定pack容量
	void SetPackOwner(IECreature * creature);			//设定pack的拥有着

	unsigned int GetPackCapacity();						//获取pack容量
	IECreature * GetPackOwner();						//获取pack拥有着

public:
	unsigned int m_packCapacity;						//pack最大容量
	IEProp ** m_props;									//pack中所有的prop
	IECreature * m_owner;								//拥有着

	IESlot * m_slot;
};

IE_END

#endif