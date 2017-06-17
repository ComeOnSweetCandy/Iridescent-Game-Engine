#define __IE_DLL_EXPORTS__
#include "IEthingCreator.h"

IE_BEGIN

int lua_fileThing_create(lua_State * luaScript)
{
	return 1;
}

int lua_usualThing_create(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TNUMBER);

	unsigned int thingID = (unsigned int)lua_tointeger(luaScript, 1);

	IEThing ** thing = ((IEThing **)lua_newuserdata(luaScript, sizeof(IEThing *)));
	*thing = IEThing::Create(thingID);

	luaL_getmetatable(luaScript, "IEThing.IEThing");
	lua_setmetatable(luaScript, -2);

	return 1;
}

int lua_interactionThing_create(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TNUMBER);

	unsigned int thingID = (unsigned int)lua_tointeger(luaScript, 1);

	IEInteractionThing ** thing = ((IEInteractionThing **)lua_newuserdata(luaScript, sizeof(IEInteractionThing *)));
	*thing = IEInteractionThing::Create(thingID);

	luaL_getmetatable(luaScript, "IEThing.IEThing");
	lua_setmetatable(luaScript, -2);

	return 1;
}

int luaopen_thingCreator(lua_State * luaScript)
{
	luaL_newmetatable(luaScript, "IEThingCreator.IEThingCreator");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_ThingCreator_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_ThingCreator_funcs);
	return 1;
}

IE_END