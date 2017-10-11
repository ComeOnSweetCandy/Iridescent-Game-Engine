/***********************************
* name     : IEArmer.h
* creater  : cosc
* info     : a creature armed with weapon
* date     : 2017/9/20
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ARMER__
#define __IE_ARMER__

#include "IECreature.h"

#include "../prop/IEPropEquipment.h"
#include "../prop/IEPropConsumable.h"
#include "../prop/IEPropPack.h"

IE_BEGIN

class __IE_DLL__ IEArmer :public IECreature
{
public:
	IEArmer();
	virtual ~IEArmer();
	virtual void Initialization(unsigned int creatureID, unsigned int creatureOrder);
	static IEArmer * Create(unsigned int creatureID, unsigned int creatureOrder);

public:
	virtual void Update();
	virtual void DrawWeapon();

	IEPropPack * GetPlayersPack();

	//设置当前装备
	void ArmEquipment(IEPropEquipment * equipment);
	void ArmWeapon(IEPropEquipment * equipment);
	void ArmHead(IEPropEquipment * equipment);

	//获取当前装备
	IEPropEquipment * GetArmedWeapon();

private:
	bool GetWeaponPosition(const char * actionName, unsigned int frapIndex, float& x, float& y, float& angle);

protected:
	IEPropPack * m_propPack;		//bag
	IEPropEquipment * m_weapon;		//equipment
	IEPropEquipment * m_head;		//head
};

IE_END

#endif