/***********************************
* name     : IECreatureEntry.h
* creater  : cosc
* info     : creature info
* date     : 2017/1/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE_INFO__
#define __IE_CREATURE_INFO__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"
#include "../../../type/IEvector.h"
#include "../../../type/IEgrid.h"

IE_BEGIN

class IECreature;

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

enum __IE_DLL__ IECreatureParty
{
	__creature_party_mine__,
	__creature_party_friend__,
	__creature_party_neutral__,
	__creature_party_enemy__
};

typedef struct ieCreatureInfo
{
	IECreatureType _CreatureType;
	float _View;
	unsigned _CreatureID;
	char _CreatureName[64];
	lua_State * _LUA;
	IEXml * _XML;

	unsigned int _BaseHealth;
	unsigned int _GrowHealth;

	unsigned int _BaseMagic;
	unsigned int _GrowMagic;

	unsigned int _BaseSpeed;
	unsigned int _GrowSpeed;

	unsigned int _BaseDamage;
	unsigned int _GrowDamage;
}IECreatureEntry;

typedef struct ieUnitInfo
{
	//map一类需要读取的信息
	IECreatureEntry * _CretureInfo;
	unsigned int _CreatrueID;
	unsigned int _Order;
	unsigned int _Level;
	IECreatureParty _Party;
	char _Name[64];

	//save一类需要读取的信息
	bool _Alive;

	//剩下的信息 是依靠于计算产生的
	unsigned int _MaxHealth;
	unsigned int _CurHealth;
	unsigned int _MaxPower;
	unsigned int _CurPower;
	unsigned int _Speed;
	unsigned int _Damage;
}IECreatureUnit;

extern "C" __IE_DLL__ bool __CreatureOpposite(IECreature * creatureA, IECreature * creatureB);

IE_END

#endif