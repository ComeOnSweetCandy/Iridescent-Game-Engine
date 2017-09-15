#define __IE_DLL_EXPORTS__
#include "IEfunctions.h"

void IEFunctionIsexistFile(const char * fileName)
{
	int exits = _access(fileName, 0);
	if (exits != 0)
	{
		FILE * fp = fopen(fileName, "wb");
		fclose(fp);
	}
}

void * LUAFunctionGetUserdate(lua_State * LUA, const char * paramName)
{
	lua_getglobal(LUA, paramName);
	void * value = *(void **)lua_touserdata(LUA, 1);
	lua_pop(LUA, 1);

	return value;
}

float LUAFunctionGetNuber(lua_State * LUA, const char * name)
{
	lua_getglobal(LUA, name);
	float value = (float)lua_tonumber(LUA, 1);
	lua_pop(LUA, 1);

	return value;
}

int LUAFunctionGetInt(lua_State * LUA, const char * name)
{
	lua_getglobal(LUA, name);
	int value = (int)lua_tonumber(LUA, -1);
	lua_pop(LUA, 1);

	return value;
}

char * LUAFunctionGetString(lua_State * LUA, const char * name)
{
	lua_getglobal(LUA, name);
	char * value = (char *)lua_tostring(LUA, 1);
	lua_pop(LUA, 1);

	return value;
}

void LUAFunctionSetUserdate(lua_State * LUA, const char * paramName, const char * className, void * data)
{
	void ** s = (void**)lua_newuserdata(LUA, sizeof(void*));
	*s = (void *)data;
	luaL_getmetatable(LUA, className);
	lua_setmetatable(LUA, -2);
	lua_setglobal(LUA, paramName);
}

bool LUAFunctionAllocateFunction(lua_State * LUA, const char * functionName)
{
	if (lua_getglobal(LUA, functionName))
	{
		return true;
	}
	else
	{
		lua_pop(LUA, -1);

		return false;
	}
}

bool LUAFunctionExecuteFunction(lua_State * LUA, const char * functionName)
{
	if (lua_getglobal(LUA, functionName))
	{
		lua_call(LUA, 0, 0);

		return true;
	}
	else
	{
		lua_pop(LUA, -1);

		return false;
	}
}