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
	__prop_equipment_type_weapon__,			//װ������� ����
	__prop_equipment_type_head__,			//װ������� ͷ��
};

class __IE_DLL__ IEPropEquipment :public IEProp
{
public:
	IEPropEquipment();
	virtual ~IEPropEquipment();
	virtual void Initialization(unsigned int propID, IEPropState propState);
	static IEPropEquipment * Create(unsigned int propID, IEPropState propState);

public:
	virtual void EquipProp();						//װ��prop
	virtual void UseProp();							//ʹ��prop
	virtual void PickProp(IEArmer * armer);			//ʰȡprop

	IEPropEquipmentType GetEquipementType();

protected:
	virtual void ArrangeInfo();				//ÿ�ε��ú� ������

private:
	void InitUnit();						//��ʼ������

protected:
	IEPropEquipmentType m_propEquipmentType;//װ������
};

IE_END

#endif