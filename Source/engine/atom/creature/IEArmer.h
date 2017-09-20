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

private:
	void ArmWeapon();

	bool GetWeaponPosition(const char * actionName, unsigned int frapIndex, float& x, float& y, float& angle);

private:
	//IEWeapon * m_weapon;
	IESprite * m_wea;
};

IE_END

#endif