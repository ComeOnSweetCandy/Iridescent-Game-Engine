#define __IE_DLL_EXPORTS__
#include "IEAtom.h"

IE_BEGIN

IEAtom::IEAtom()
{
	m_physicNode = NULL;
}

IEAtom::~IEAtom()
{
	
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

void IEAtom::SetTranslate(const float &x, const float &y)
{
	IENode::SetTranslate(x, y);

	if (m_physicNode)
	{
		m_physicNode->SetPhysicPosition(x, y);
	}
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

void IEAtom::ChangeGroup(const char * groupName, unsigned int sameIndex, unsigned int playTimes, IEFunctionTexturePlayEnded playEndedFunction)
{
	IESprite::ChangeGroup(groupName, sameIndex, playTimes, this, playEndedFunction);
}

IE_END