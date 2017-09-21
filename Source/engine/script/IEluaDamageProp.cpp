//#define __IE_DLL_EXPORTS__
//#include "IEluaDamageProp.h"
//
////#include "IEluaNode.h"
//
//IE_BEGIN
//
//int lua_damageProp_create(lua_State * LUA)
//{
//	luaL_checktype(LUA, 1, LUA_TNUMBER);
//	luaL_checktype(LUA, 2, LUA_TUSERDATA);
//	luaL_checktype(LUA, 3, LUA_TUSERDATA);
//	luaL_checktype(LUA, 4, LUA_TNUMBER);
//
//	int propIndex = (int)lua_tointeger(LUA, 1);
//	IETrigger * trigger = *((IETrigger**)lua_touserdata(LUA, 2));
//	IECreature * propOwner = *((IECreature**)lua_touserdata(LUA, 3));
//	int damageValue = (int)lua_tointeger(LUA, 4);
//
//	IEDamageProp ** prop = (IEDamageProp **)lua_newuserdata(LUA, sizeof(IEDamageProp *));
//	*prop = IEDamageProp::Create(propIndex, trigger, propOwner, damageValue);
//
//	luaL_getmetatable(LUA, "IEProp.IEProp");
//	lua_setmetatable(LUA, -2);
//
//	return 1;
//}
//
//int luaopen_damageProp(lua_State * LUA)
//{
//	luaL_newmetatable(LUA, "IEDamageProp.IEDamageProp");
//	lua_pushvalue(LUA, -1);
//	lua_setfield(LUA, -2, "__index");
//	luaL_setfuncs(LUA, lua_reg_damageProp_funcs_m, 0);
//	luaL_newlib(LUA, lua_reg_damageProp_funcs);
//	return 1;
//}
//
//IE_END