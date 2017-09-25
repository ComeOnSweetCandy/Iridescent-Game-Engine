/***********************************
* name     : IECreatureList.h
* creater  : cosc
* info     : all creatures manager
* date     : 2017/2/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CREATURE_LIST__
#define __IE_CREATURE_LIST__

#include "../../../global/IEstdafx.h"
#include "../../../tools/IEXml.h"

IE_BEGIN

enum __IE_DLL__ IECreatureRace
{
	__creature_race_human__,
	__creature_race_animal__,
	__creature_race_machine__,
	__creature_race_ghost__,
	__creature_race_devil__,
	__creature_race_monster__,
	__creature_race_unknown__
};

enum __IE_DLL__ IECreatureParty
{
	__creature_party_mine__,
	__creature_party_friend__,
	__creature_party_neutral__,
	__creature_party_enemy__
};

enum __IE_DLL__ IECreaturePart
{
	__creature_part_body__,			//主体动作改变
	__creature_part_leg__,			//腿部动作改变
	__creature_part_max__,			//计数
};

//creature的信息列表
typedef struct ieCreatureEntry
{
	//最基础用来查找的属性
	unsigned _CreatureID;
	char _CreatureName[64];

	//基础属性数据属性
	IECreatureRace _CreatureType;
	float _View;

	unsigned int _BaseHealth;
	unsigned int _GrowHealth;

	unsigned int _BaseMagic;
	unsigned int _GrowMagic;

	unsigned int _BaseSpeed;
	unsigned int _GrowSpeed;

	unsigned int _BaseDamage;
	unsigned int _GrowDamage;

	lua_State * _LUA;
	IEXml * _XML;
}IECreatureEntry;

//个人的信息
typedef struct ieCreatureUnit
{
	//map一类需要读取的信息
	char _UnitName[64];
	unsigned int _CreatrueID;
	unsigned int _Order;
	unsigned int _Level;
	IECreatureParty _Party;

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

//Creatures的信息列表
class IECreatureList
{
public:
	IECreatureList();
	virtual ~IECreatureList();
	virtual void Initialization();
	virtual void Release();
	static IECreatureList * Share();

public:
	IECreatureEntry * GetEntrys();
	unsigned int GetEntrysCount();

	void AddEntry(const char * creatureName);
	void DelEntry(const char * creatureName);
	void DelEntry(unsigned int creatureID);
	
	void LoadList();
	void SaveList();

private:
	static IECreatureList * m_staticList;

	IECreatureEntry * m_entrys;
	unsigned int m_entrysCount;

	friend class IECreature;
};

IE_END

#endif