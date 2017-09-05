#define __IE_DLL_EXPORTS__
#include "IEluaCollisionTrigger.h"

IE_BEGIN

int lua_collisionTrigger_create(lua_State* luaSript)
{
	//luaL_checktype(luaSript, 1, LUA_TUSERDATA);
	//luaL_checktype(luaSript, 2, LUA_TNUMBER);
	//luaL_checktype(luaSript, 3, LUA_TNUMBER);

	//IEPhysicEdge * physicEdge = *((IEPhysicEdge **)lua_touserdata(luaSript, 1));
	//IEPhysicNodeType physicNodeType = (IEPhysicNodeType)lua_tointeger(luaSript, 2);
	//IEClockType clockType = (IEClockType)lua_tointeger(luaSript, 3);
	//int clockParam = (int)lua_tointeger(luaSript, 4);

	//IECollisionTrigger ** collisionTrigger = (IECollisionTrigger**)lua_newuserdata(luaSript, sizeof(IECollisionTrigger*));
	//*collisionTrigger = IECollisionTrigger::Create(physicEdge, physicNodeType, clockType, clockParam);

	//luaL_getmetatable(luaSript, "IECollisionTrigger.IECollisionTrigger");
	//lua_setmetatable(luaSript, -2);

	//return 1;
	return 1;
}

int luaopen_collisionTrigger(lua_State *luaSript)
{
	luaL_newmetatable(luaSript, "IECollisionTrigger.IECollisionTrigger");
	lua_pushvalue(luaSript, -1);
	lua_setfield(luaSript, -2, "__index");
	luaL_setfuncs(luaSript, lua_reg_collisionTrigger_funcs_m, 0);
	luaL_newlib(luaSript, lua_reg_collisionTrigger_funcs);
	return 1;
}

IE_END