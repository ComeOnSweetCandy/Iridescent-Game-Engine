/***********************************
* name     : IEPropConsumable.h
* creater  : cosc
* info     : every prop in scene
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP_CONSUMABLE__
#define __IE_PROP_CONSUMABLE__

#include "IEProp.h"

IE_BEGIN

typedef enum IEPropEquipmentType
{
	__prop_equipment_type_weapon__,			//װ������� ����
	__prop_equipment_type_head__,			//װ������� ͷ��
};

class __IE_DLL__ IEPropConsumable :public IEProp
{
public:
	IEPropConsumable();
	virtual ~IEPropConsumable();
	virtual void Initialization(unsigned int propID, IEPropState propState);
	static IEPropConsumable * Create(unsigned int propID, IEPropState propState);

public:
	virtual void EquipProp();						//װ��prop
	virtual void UseProp();							//ʹ��prop
	virtual void PickProp(IEArmer * armer);			//ʰȡprop

protected:
	virtual void ArrangeInfo();				//ÿ�ε��ú� ������

private:
	void InitUnit();						//��ʼ������

protected:

};

IE_END

#endif