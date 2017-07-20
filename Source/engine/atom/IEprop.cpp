#define __IE_DLL_EXPORTS__
#include "IEProp.h"
#include "creature/IECreature.h"

#include "prop/IEpropsInfoManager.h"

#include "../../interface/cmd/IEapplication.h"

#include "../script/IEluaCreature.h"
#include "../script/IEluaCollisionTrigger.h"
#include "../script/IEluaPhysicCircle.h"
#include "../script/IEluaPhysicNode.h"
#include "../script/IEluaNode.h"
#include "../script/IEluaProp.h"
#include "../script/IEluaDamageProp.h"

IE_BEGIN

IEProp::IEProp()
{
	m_propType = __prop_type_count__;
	m_propCount = 1;
	m_propIndex = 0;
	m_owner = NULL;
	m_luaScript = NULL;
}

IEProp::~IEProp()
{
	m_owner = NULL;
}

void IEProp::Initialization(int propIndex, IETrigger * trigger)
{
	IEAtom::Initialization();
	IEElement::SetRegularization(true);
	IENode::SetDrawMode(false);

	SetPropIndex(propIndex);
	BindTrigger(trigger);

	AddSelfToPropLayer();
	SetAnchor(0.5f, 0.5f);
}

IEProp * IEProp::Create(int propIndex, IETrigger * trigger)
{
	IEProp * prop = new IEProp();
	prop->Initialization(propIndex, trigger);
	return prop;
}

void IEProp::BindTrigger(IETrigger * trigger)
{
	if (trigger == NULL)
	{
		ClearTriggers();
	}
	else
	{
		IETriggerType triggerType = trigger->GetTriggerType();

		if (m_triggers[triggerType] != NULL)
		{
			__IE_WARNING__("IEProp : warning . m_trigger deserve not equal null.\n");
		}
		else
		{
			m_triggers[triggerType] = trigger;
			m_triggers[triggerType]->BindNode(this);
		}
	}
}

void IEProp::ClearTriggers()
{
	for (int index = 0; index < __trigger_type_count__; index++)
	{
		if (m_triggers[index])
		{
			m_triggers[index]->SetClockEnd();
			m_triggers[index]->BindNode(NULL);
			m_triggers[index] = NULL;
		}
	}
}

void IEProp::AddSelfToPropLayer()
{
	IEApplication::Share()->GetCurrentActiveScene()->GetPropLayer()->AddChild(this);
}

void IEProp::SetLuaScript(lua_State * m_luaScript)
{
	m_luaScript = m_luaScript;
	char * propName = GetLuaStringElement(m_luaScript, "propName");

	ChangeTexture(propName);
}

void IEProp::InitLuaScript()
{
	IEPropInfo info = IEPropsInfoManager::Share()->LoadPropInfo(m_propIndex);
	IEString scriptName = IEString("../Debug/data/script/prop/") + info.s_name + ".lua";
	m_luaScript = luaL_newstate();
	luaL_openlibs(m_luaScript);

	luaL_Reg lua_reg_libs[] =
	{
		{ "base", luaopen_base },
		{ "IEPhysicCircle", luaopen_physicCircle },
		{ "IEPhysicNode", luaopen_physicNode },
		{ "IECollisionTrigger", luaopen_collisionTrigger },
		{ "IEDamageProp", luaopen_damageProp },
		{ "IECreature", luaopen_creature },
		{ "IENode", luaopen_node },
		{ "IEProp", luaopen_prop },
		{ NULL, NULL }
	};

	for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
	{
		luaL_requiref(m_luaScript, lua_reg->name, lua_reg->func, 1);
		lua_pop(m_luaScript, 1);
	}

	if (luaL_dofile(m_luaScript, scriptName.GetString()) != 0)
	{
		__IE_WARNING__("IEAttack : can not find m_luaScript file.\n");
	}
}

void IEProp::ChangePropTexture(char * textureTypeName)
{
	char * textureFile = GetLuaStringElement(m_luaScript, textureTypeName);
	ChangeTexture(textureFile);
}

char * IEProp::GetPropTexture(char * textureTypeName)
{
	char * textureFile = GetLuaStringElement(m_luaScript, textureTypeName);
	return textureFile;
}

void IEProp::ClockTick()
{
	ClearTriggers();
	RemoveFromParent();
}

void IEProp::InteractiveNode(IENode * strikeNode)
{

}

void IEProp::SetPropOwner(IECreature * creature)
{
	m_owner = creature;
}

IECreature * IEProp::GetPropOwner()
{
	return m_owner;
}

IEPropType IEProp::GetPropType()
{
	return m_propType;
}

void IEProp::SetPropIndex(int propIndex)
{
	m_propIndex = propIndex;

	InitLuaScript();
}

int IEProp::GetPropIndex()
{
	return m_propIndex;
}

void IEProp::SetPropCount(int count)
{
	if (count == 0)
	{
		__IE_WARNING__("IEProp : error.\n");
	}
	m_propCount = count;
}

int IEProp::GetPropCount()
{
	return m_propCount;
}

void IEProp::AddPropCount(int count)
{
	m_propCount = m_propCount + count;
}

void IEProp::ReducePropCount(int count)
{
	m_propCount = m_propCount - count;

	if (m_propCount < 0)
	{
		__IE_WARNING__("IEUsedProp : error . the prop count less than zeor.\n");
	}
}

IE_END