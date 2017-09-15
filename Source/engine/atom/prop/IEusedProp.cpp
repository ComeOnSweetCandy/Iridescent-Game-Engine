#define __IE_DLL_EXPORTS__
#include "IEusedProp.h"
#include "IEpropPack.h"

#include "../creature/IEplayer.h"

IE_BEGIN

IEUsedProp::IEUsedProp()
{
	m_propType = __prop_used_type__;
	m_propPack = NULL;
}

IEUsedProp::~IEUsedProp()
{

}

void IEUsedProp::Initialization(int propIndex, int propCount)
{
	SetPropIndex(propIndex);
	SetPropCount(propCount);
	BindTrigger(NULL);

	ChangePropTexture("propIcon");
}

IEUsedProp * IEUsedProp::Create(int propIndex, int propCount)
{
	IEUsedProp * prop = new IEUsedProp();
	prop->Initialization(propIndex, propCount);
	return prop;
}

void IEUsedProp::ClockTick()
{
	delete this;
}

void IEUsedProp::PressCallback(IENode * widget)
{
	UseProp();
}

void IEUsedProp::UseProp()
{
	ReducePropCount();
	UsePropScript();
	if (m_propCount == 0)
	{
		m_propPack->DeleteProp(this);
	}
	else
	{
		m_propPack->UpdateUI();
	}
}

void IEUsedProp::UsePropScript()
{
	LUASetUserdate(m_LUA, "actionNode", "IECreature.IECreature", m_owner);
	LUASetUserdate(m_LUA, "actionPhysicNode", "IEPhysicNode.IEPhysicNode", m_owner->GetPhysicNode());

	//执行施放函数
	lua_getglobal(m_LUA, "UserProp");
	lua_call(m_LUA, 0, 0);
}

void IEUsedProp::SetPropPack(IEPropPack * propPack)
{
	m_propPack = propPack;
}

IE_END