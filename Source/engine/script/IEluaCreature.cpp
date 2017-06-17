#define __IE_DLL_EXPORTS__
#include "IEluaCreature.h"

IE_BEGIN

int lua_creature_create(lua_State* lua)
{
	return 1;
}

int lua_creature_getFacer(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));
	IEGrid faceDirection = creature->GetDirection();

	lua_pushinteger(lua, faceDirection.m_x);
	lua_pushinteger(lua, faceDirection.m_y);

	return 2;
}

int lua_creature_cure(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);
	luaL_checktype(lua, 2, LUA_TNUMBER);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));
	int cureValue = (int)lua_tointeger(lua, 2);

	creature->Cured(cureValue);

	return 0;
}

int lua_follow_enemy(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));

	creature->FollowEnemy();

	return 0;
}

int luaopen_creature(lua_State *lua)
{
	luaL_newmetatable(lua, "IECreature.IECreature");
	lua_pushvalue(lua, -1);
	lua_setfield(lua, -2, "__index");
	luaL_setfuncs(lua, lua_reg_creature_funcs_m, 0);
	luaL_newlib(lua, lua_reg_creature_funcs);
	return 1;
}

IE_END