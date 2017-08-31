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

	__IE_LUA_RELEASE__(m_script);
}

void IEAtom::Initialization()
{
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

void IEAtom::SetTextureGroupName(const char * textureGroupName)
{
	m_textureGroupName = textureGroupName;
}

const char * IEAtom::GetTextureGroupName()
{
	return m_textureGroupName.GetString();
}

lua_State * IEAtom::GetLuaScript()
{
	return m_script;
}

void IEAtom::ChangeState(unsigned stateIndex)
{
	IEXml * state = m_XML->FindChild("state",stateIndex);


}

IE_END