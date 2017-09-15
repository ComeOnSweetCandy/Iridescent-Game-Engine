#define __IE_DLL_EXPORTS__
#include "IEluaThing.h"

IE_BEGIN

int lua_thing_create(lua_State * LUA)
{
	return 1;
}

int luaopen_thing(lua_State * LUA)
{
	luaL_newmetatable(LUA, "IEThing.IEThing");
	lua_pushvalue(LUA, -1);
	lua_setfield(LUA, -2, "__index");
	luaL_setfuncs(LUA, lua_reg_Thing_funcs_m, 0);
	luaL_newlib(LUA, lua_reg_Thing_funcs);
	return 1;
}

IE_END