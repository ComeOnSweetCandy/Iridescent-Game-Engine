#define __IE_DLL_EXPORTS__
#include "IEfunctions.h"

float GetLuaFloatElement(lua_State * luaScript, const char * name)
{
	//lua_settop(luaScript, 0);
	lua_getglobal(luaScript, name);
	float value = (float)lua_tonumber(luaScript, 1);
	lua_pop(luaScript, 1);
	return value;
}

int GetLuaIntElement(lua_State * luaScript, const char * name)
{
	//lua_settop(luaScript, 0);
	if (lua_getglobal(luaScript, name))
	{
		int value = (int)lua_tonumber(luaScript, -1);
		lua_pop(luaScript, 1);
		return value;
	}

	return 0;
}

char * GetLuaStringElement(lua_State * luaScript, const char * name)
{
	//lua_settop(luaScript, 0);
	lua_getglobal(luaScript, name);
	char * value = (char *)lua_tostring(luaScript, 1);
	lua_pop(luaScript, 1);
	return value;
}

void SetLuaUserdataElement(lua_State * luaScript, const char * paramName, const char * className, void * data)
{
	void ** s = (void**)lua_newuserdata(luaScript, sizeof(void*));
	*s = (void *)data;
	luaL_getmetatable(luaScript, className);
	lua_setmetatable(luaScript, -2);
	lua_setglobal(luaScript, paramName);
}

void * GetLuaUserdataElement(lua_State * luaScript, const char * paramName)
{
	//lua_settop(luaScript, 0);
	if (!(lua_getglobal(luaScript, paramName)))
	{
		return NULL;
	}
	void * value = *(void **)lua_touserdata(luaScript, 1);
	lua_pop(luaScript, 1);
	return value;
}