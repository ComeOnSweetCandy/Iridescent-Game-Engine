/***********************************
* name     : IEluaPhysicCircle.h
* creater  : cosc
* info     : script physic circle
* date     : 2017/3/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_PHYSIC_CIRCLE__
#define __IE_LUA_PHYSIC_CIRCLE__

#include "../../global/IEstdafx.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_physicCircle_create(lua_State* luaSript);

extern "C" __IE_DLL__ int lua_physicCircle_setRadius(lua_State* luaSript);
extern "C" __IE_DLL__ int lua_physicCircle_getRadius(lua_State* luaSript);

static const luaL_Reg lua_reg_physicCircle_funcs[] = {
	{ "Create", lua_physicCircle_create },
	{ "SetRadius", lua_physicCircle_setRadius },
	{ "GetRadius", lua_physicCircle_getRadius },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_physicCircle_funcs_m[] = {
	{ "SetRadius", lua_physicCircle_setRadius },
	{ "GetRadius", lua_physicCircle_getRadius },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_physicCircle(lua_State *luaSript);

IE_END

#endif