/***********************************
* name     : IEluaPhysicPolygon.h
* creater  : cosc
* info     : script physic polygon
* date     : 2017/3/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_PHYSIC_POLYGON__
#define __IE_LUA_PHYSIC_POLYGON__

#include "../../global/IEstdafx.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_physicPolygon_create(lua_State * luaSript);

static const luaL_Reg lua_reg_physicPolygon_funcs[] = {
	{ "Create", lua_physicPolygon_create },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_physicPolygon_funcs_m[] = {
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_physicPolygon(lua_State * luaSript);

IE_END

#endif