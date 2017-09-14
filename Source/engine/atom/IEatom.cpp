#define __IE_DLL_EXPORTS__
#include "IEAtom.h"

IE_BEGIN

IEAtom::IEAtom()
{
	m_physicNode = NULL;
}

IEAtom::~IEAtom()
{
	//Die();

	__IE_LUA_RELEASE__(m_LUA);
}

void IEAtom::Initialization()
{
	IEElement::SetRegularization(true);
	IESprite::Initialization(NULL);

	Born();
}

IEAtom * IEAtom::Create()
{
	IEAtom * atom = new IEAtom();
	atom->Initialization();
	return atom;
}

void IEAtom::Update()
{
	IENode::Update();

	Live();
}

void IEAtom::Born()
{

}

void IEAtom::Live()
{

}

void IEAtom::Die()
{

}

lua_State * IEAtom::GetLuaScript()
{
	return m_LUA;
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