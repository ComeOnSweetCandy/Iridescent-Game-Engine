//#define __IE_DLL_EXPORTS__
//#include "IEluaProp.h"
//
//#include "../scene/thing/IEthingArea.h"
//#include "../scene/thing/items/IETorch.h"
//#include "../../interface/cmd/IEapplication.h"
//
//IE_BEGIN
//
//int lua_prop_create(lua_State * LUA)
//{
//	__IE_WARNING__("IELuaProp : error.\n");
//
//	luaL_checktype(LUA, 1, LUA_TNUMBER);
//	luaL_checktype(LUA, 2, LUA_TUSERDATA);
//
//	int propIndex = (int)lua_tointeger(LUA, 1);
//	IETrigger * trigger = *((IETrigger **)lua_touserdata(LUA, 2));
//
//	IEProp ** prop = (IEProp**)lua_newuserdata(LUA, sizeof(IEProp*));
//	*prop = IEProp::Create(propIndex, trigger);
//
//	luaL_getmetatable(LUA, "IEProp.IEProp");
//	lua_setmetatable(LUA, -2);
//
//	return 1;
//}
//
//int lua_prop_bindTrigger(lua_State * LUA)
//{
//	luaL_checktype(LUA, 1, LUA_TUSERDATA);
//	luaL_checktype(LUA, 2, LUA_TUSERDATA);
//
//	IEProp * prop = *((IEProp **)lua_touserdata(LUA, 1));
//	IETrigger * trigger = *((IETrigger**)lua_touserdata(LUA, 2));
//
//	prop->BindTrigger(trigger);
//
//	lua_settop(LUA, 0);
//
//	return 0;
//}
//
//int lua_prop_createFire(lua_State * LUA)
//{
//	luaL_checktype(LUA, 1, LUA_TNUMBER);
//	float lightDistance = (float)lua_tonumber(LUA, 1);
//
//	IETotalScene * scene = IEApplication::Share()->GetCurrentActiveScene();
//	const float * position = scene->GetPlayer()->GetTranslate();
//
//	scene->GetBindedMap()->GetThing()->SetReadyThing(2);
//	scene->GetBindedMap()->GetThing()->AddChild(position[0], position[1], 0, 0);
//
//	return 0;
//}
//
//int luaopen_prop(lua_State * LUA)
//{
//	luaL_newmetatable(LUA, "IEProp.IEProp");
//	lua_pushvalue(LUA, -1);
//	lua_setfield(LUA, -2, "__index");
//	luaL_setfuncs(LUA, lua_reg_Prop_funcs_m, 0);
//	luaL_newlib(LUA, lua_reg_Prop_funcs);
//	return 1;
//}
//
//IE_END