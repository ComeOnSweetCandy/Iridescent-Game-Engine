/***********************************
* name     : IEcreatureInfo.h
* creater  : cosc
* info     : creature info
* date     : 2017/1/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE_INFO__
#define __IE_CREATURE_INFO__

#include "../../../global/IEstdafx.h"
#include "../../../type/IEvector.h"
#include "../../../type/IEgrid.h"

IE_BEGIN

enum __IE_DLL__ IECreatureType
{
	__creature_type_human__,
	__creature_type_animal__,
	__creature_type_machine__,
	__creature_type_ghost__,
	__creature_type_devil__,
	__creature_type_monster__,
	__creature_type_unknown__
};

enum __IE_DLL__ IECreatureGroup
{
	__creature_group_mine__,
	__creature_group_friend__,
	__creature_group_neutral__,
	__creature_group_enemy__
};

typedef struct ieUnitInfo
{
	ieUnitInfo()
	{
		//绝对需要读取unit信息 最大可能同map一类
		_CreatrueID = 1;
		_UnitOrder = 1;
		_UnitGroup = __creature_group_mine__;
		strcpy(_UnitName, "steven");
		_Level = 1;

		//绝对需要确认的信息 最大可能从save一类
		_Alive = true;
	};
	
	//map一类需要读取的信息
	unsigned int _CreatrueID;
	unsigned int _UnitOrder;
	unsigned int _Level;
	IECreatureGroup _UnitGroup;
	char _UnitName[64];

	//save一类需要读取的信息
	bool _Alive;

	//剩下的信息 是依靠于计算产生的
	unsigned int _MaxHealth;
	unsigned int _CurHealth;
	unsigned int _MaxPower;
	unsigned int _CurPower;
	unsigned int _Speed;
	unsigned int _Damage;
}IEUnitInfo;

typedef struct ieCreatureInfo
{
	IECreatureType _CreatureType;
	char _CreatureName[64];

	unsigned int _BaseHealth;
	unsigned int _GrowHealth;

	unsigned int _BasePower;
	unsigned int _GrowPower;

	unsigned int _BaseSpeed;
	unsigned int _GrowSpeed;

	unsigned int _BaseDamage;
	unsigned int _GrowDamage;
}IECreatureInfo;

IE_END

#endif