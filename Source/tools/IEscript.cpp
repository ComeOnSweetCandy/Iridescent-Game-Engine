#define __IE_DLL_EXPORTS__
#include "IEscript.h"

#include "../core/container/IEdictionary.h"

IE_BEGIN

IEScript::IEScript()
{
	m_script = NULL;
}

IEScript::~IEScript()
{
	__IE_LUA_RELEASE__(m_script);
}

void IEScript::Initialization(const char * scriptName)
{
	RESOURCE[scriptName] = (IEObject *)this;
}

IEScript * IEScript::Create(const char * scriptName)
{
	IEObject * resource = RESOURCE[scriptName];
	if (resource == NULL)
	{
		IEScript * script = new IEScript();
		script->Initialization(scriptName);
		return script;
	}
	else
	{
		return (IEScript *)resource;
	}
}

void IEScript::SetLuaScript(lua_State * luaScript)
{
	m_script = luaScript;
}

lua_State * IEScript::GetLuaScript()
{
	return m_script;
}

IE_END