/***********************************
* name     : IEprop.h
* creater  : cosc
* info     : every prop in scene
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PROP__
#define __IE_PROP__

#include "IEatom.h"
#include "../trigger/IEtrigger.h"

IE_BEGIN

class IECollisionTrigger;
class IEInteractionTrigger;

enum IEPropType
{
	__prop_interaction_type__,		/* press e or collision */
	__prop_picked_type__,		    /* press e */
	__prop_damage_type__,           /* collision */
	__prop_used_type__,
	__prop_type_count__
};

class __IE_DLL__ IEProp :public IEAtom
{
public:
	IEProp();
	virtual ~IEProp();
	virtual void Initialization(int propIndex, IETrigger * trigger);
	static IEProp * Create(int propIndex, IETrigger * trigger);

public:
	virtual void ClockTick();
	virtual void BindTrigger(IETrigger * trigger);
	virtual void ClearTriggers();
	virtual void InteractiveNode(IENode * strikeNode);

	void SetLuaScript(lua_State * luaScript);
	void InitLuaScript();
	void ChangePropTexture(char * textureTypeName);
	char * GetPropTexture(char * textureTypeName);

	void AddSelfToPropLayer();

	void SetPropOwner(IECreature * creature);
	IECreature * GetPropOwner();
	IEPropType GetPropType();
	void SetPropIndex(int propIndex);
	int GetPropIndex();
	void SetPropCount(int propCount);
	void AddPropCount(int propCount = 1);
	void ReducePropCount(int count = 1);
	int GetPropCount();

protected:
	int m_propCount;
	int m_propIndex;
	IEPropType m_propType;
	IECreature * m_owner;
	IETrigger * m_triggers[__trigger_type_count__];
};

IE_END

#endif