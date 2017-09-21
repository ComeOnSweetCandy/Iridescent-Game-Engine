/***********************************
* name     : IEPropEquipment.h
* creater  : cosc
* info     : every prop in scene
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_EQUIPMENT__
#define __IE_PROP_EQUIPMENT__

#include "IEProp.h"

IE_BEGIN

typedef enum IEPropEquipmentType
{
	__prop_equipment_type_weapon__,			//装备类道具 武器
	__prop_equipment_type_head__,			//装备类道具 头部
};

class __IE_DLL__ IEPropEquipment :public IEProp
{
public:
	IEPropEquipment();
	virtual ~IEPropEquipment();
	virtual void Initialization(unsigned int propID, IEPropState propState);
	static IEPropEquipment * Create(unsigned int propID, IEPropState propState);

public:
	virtual void EquipProp();						//装备prop
	virtual void UseProp();							//使用prop
	virtual void PickProp(IECreature * creature);	//拾取prop

protected:
	virtual void ArrangeInfo();				//每次调用后 自身处理

private:
	void InitUnit();						//初始化自身

protected:
};

IE_END

#endif