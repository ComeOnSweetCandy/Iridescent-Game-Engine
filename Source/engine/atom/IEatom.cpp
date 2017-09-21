#define __IE_DLL_EXPORTS__
#include "IEAtom.h"

IE_BEGIN

IEAtom::IEAtom()
{
	m_physicNode = NULL;
}

IEAtom::~IEAtom()
{
	__IE_LUA_RELEASE__(m_LUA);
}

void IEAtom::Initialization()
{
	IEElement::SetRegularization(true);
	IESprite::Initialization(NULL);
}

IEAtom * IEAtom::Create()
{
	IEAtom * atom = new IEAtom();
	atom->Initialization();
	return atom;
}

lua_State * IEAtom::GetLuaScript()
{
	return m_LUA;
}

void IEAtom::ArrangeInfo()
{
	//do something
}

void IEAtom::AddTrigger(IETrigger * trigger)
{

}

void IEAtom::AddTrigger(IETrigger * trigger, const char * functionLua)
{

}

void IEAtom::DelTrigger(IETriggerType type)
{

}

void IEAtom::TriggerStrike(IEPhysicNode * physicNode)
{

}

void IEAtom::ChangeState(const char * stateName)
{
	ChangeAssort(stateName);
}

void IEAtom::ChangeGroup(const char * groupName, unsigned int sameIndex)
{
	IESprite::ChangeGroup(groupName, sameIndex);
}

IE_END