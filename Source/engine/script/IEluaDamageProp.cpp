#define __IE_DLL_EXPORTS__
#include "IEluaDamageProp.h"

//#include "IEluaNode.h"

IE_BEGIN

int lua_damageProp_create(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TNUMBER);
	luaL_checktype(luaScript, 2, LUA_TUSERDATA);
	luaL_checktype(luaScript, 3, LUA_TUSERDATA);
	luaL_checktype(luaScript, 4, LUA_TNUMBER);

	int propIndex = (int)lua_tointeger(luaScript, 1);
	IETrigger * trigger = *((IETrigger**)lua_touserdata(luaScript, 2));
	IECreature * propOwner = *((IECreature**)lua_touserdata(luaScript, 3));
	int damageValue = (int)lua_tointeger(luaScript, 4);

	IEDamageProp ** prop = (IEDamageProp **)lua_newuserdata(luaScript, sizeof(IEDamageProp *));
	*prop = IEDamageProp::Create(propIndex, trigger, propOwner, damageValue);

	luaL_getmetatable(luaScript, "IEProp.IEProp");
	lua_setmetatable(luaScript, -2);

	return 1;
}

int luaopen_damageProp(lua_State * luaScript)
{
	luaL_newmetatable(luaScript, "IEDamageProp.IEDamageProp");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_damageProp_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_damageProp_funcs);
	return 1;
}

IE_END