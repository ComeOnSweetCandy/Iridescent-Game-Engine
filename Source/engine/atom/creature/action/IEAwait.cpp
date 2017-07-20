#define __IE_DLL_EXPORTS__
#include "IEawait.h"

#include "../IECreature.h"

IE_BEGIN

IEAwait::IEAwait()
{
	m_actionType = __action_await__;
	m_actionLevel = __actionlevel_0__;
	m_waitTime = 0.0f;
}

IEAwait::~IEAwait()
{

}

void IEAwait::Initialization()
{

}

IEAwait * IEAwait::Create()
{
	IEAwait * state = new IEAwait();
	state->Initialization();
	return state;
}

bool IEAwait::Begin()
{
	ChangeActionTexture("await");
	DeleteOtherActions();

	lua_State * luaScript = GetActionCreature()->GetLuaScript();
	if (lua_getglobal(luaScript, "await"))
	{
		lua_call(luaScript, 0, 0);
	}
	else
	{
		
	}



	return true;
}

bool IEAwait::Excute()
{
	return true;
}

bool IEAwait::End()
{
	return true;
}

IE_END