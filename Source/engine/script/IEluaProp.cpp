#define __IE_DLL_EXPORTS__
#include "IEluaProp.h"

#include "../scene/thing/IEthingArea.h"
#include "../scene/thing/items/IETorch.h"
#include "../../interface/cmd/IEapplication.h"

IE_BEGIN

int lua_prop_create(lua_State * luaScript)
{
	__IE_WARNING__("IELuaProp : error.\n");

	luaL_checktype(luaScript, 1, LUA_TNUMBER);
	luaL_checktype(luaScript, 2, LUA_TUSERDATA);

	int propIndex = (int)lua_tointeger(luaScript, 1);
	IETrigger * trigger = *((IETrigger **)lua_touserdata(luaScript, 2));

	IEProp ** prop = (IEProp**)lua_newuserdata(luaScript, sizeof(IEProp*));
	*prop = IEProp::Create(propIndex, trigger);

	luaL_getmetatable(luaScript, "IEProp.IEProp");
	lua_setmetatable(luaScript, -2);

	return 1;
}

int lua_prop_bindTrigger(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TUSERDATA);
	luaL_checktype(luaScript, 2, LUA_TUSERDATA);

	IEProp * prop = *((IEProp **)lua_touserdata(luaScript, 1));
	IETrigger * trigger = *((IETrigger**)lua_touserdata(luaScript, 2));

	prop->BindTrigger(trigger);

	lua_settop(luaScript, 0);

	return 0;
}

int lua_prop_createFire(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TNUMBER);
	float lightDistance = (float)lua_tonumber(luaScript, 1);

	IETotalScene * scene = IEApplication::Share()->GetCurrentActiveScene();
	const float * position = scene->GetPlayer()->GetTranslate();

	scene->GetBindedMap()->GetThing()->SetReadyThing(2);
	scene->GetBindedMap()->GetThing()->AddChild(position[0], position[1], 0, 0);

	return 0;
}

int luaopen_prop(lua_State * luaScript)
{
	luaL_newmetatable(luaScript, "IEProp.IEProp");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_Prop_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_Prop_funcs);
	return 1;
}

IE_END