/***********************************
* name     : IEthingCreator.h
* creater  : cosc
* info     : thing Creator
* date     : 2017/5/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THING_CREATOR__
#define __IE_THING_CREATOR__

#include "IEfire.h"
#include "IEinteractionThing.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_usualThing_create(lua_State * luaScript);
extern "C" __IE_DLL__ int lua_fileThing_create(lua_State * luaScript);
extern "C" __IE_DLL__ int lua_interactionThing_create(lua_State * luaScript);

static const luaL_Reg lua_reg_ThingCreator_funcs[] = {
	{ "CreateThing", lua_usualThing_create },
	{ "CreateFireThing", lua_fileThing_create },
	{ "CreateInteractionThing", lua_interactionThing_create },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_ThingCreator_funcs_m[] = {
	{ "CreateThing", lua_usualThing_create },
	{ "CreateFireThing", lua_fileThing_create },
	{ "CreateInteractionThing", lua_interactionThing_create },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_thingCreator(lua_State * luaScript);

IE_END

#endif