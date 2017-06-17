#define __IE_DLL_EXPORTS__
#include "IEluaThing.h"

IE_BEGIN

int lua_thing_create(lua_State * luaScript)
{
	return 1;
}

int luaopen_thing(lua_State * luaScript)
{
	luaL_newmetatable(luaScript, "IEThing.IEThing");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_Thing_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_Thing_funcs);
	return 1;
}

IE_END