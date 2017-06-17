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

#include "IEusedProp.h"

IE_BEGIN

class IESlot;

class __IE_DLL__ IEPropPack:public IEObject
{
public:
	IEPropPack();
	virtual ~IEPropPack();
	virtual void Initialization(IECreature * creature, int packCapacity);
	static IEPropPack * Create(IECreature * creature, int packCapacity);
	static IEPropPack * CreateAndRetain(IECreature * creature, int packCapacity);

public:
	//更新绑定的UI
	virtual void UpdateUI();

	void SetPackCapacity(int packCapacity);
	void SetSlot(IESlot * shortCut);

	void InsertProp(IEProp * prop);
	void DeleteProp(IEUsedProp * prop);
	void DropProp(IEUsedProp * prop);
	void UseProp(int packIndex);
	bool HaveProp(int packIndex);

	void SetPackOwner(IECreature * creature);
	IECreature * GetPackOwner();

public:
	int m_packOccupy;
	int m_packCapacity;
	IEUsedProp ** m_props;
	IECreature * m_packOwner;

	IESlot * m_slot;
};

IE_END

#endif