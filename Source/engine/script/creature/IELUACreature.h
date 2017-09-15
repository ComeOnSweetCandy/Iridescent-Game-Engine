/***********************************
* name     : IELUACreature.h
* creater  : cosc
* info     : LUA script node
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_CREATURE__
#define __IE_LUA_CREATURE__

#include "../../atom/creature/IECreature.h"

IE_BEGIN

extern "C" __IE_DLL__ int LUAInitCreature(lua_State *luaSript);

extern "C" __IE_DLL__ int LUAFunction_GetFacer(lua_State * LUA);
extern "C" __IE_DLL__ int LUAFunction_AroundEnemys(lua_State * LUA);

static const luaL_Reg lua_reg_creature_funcs_m[] = {
	{ "GetFacer", LUAFunction_GetFacer },
	{ "AroundEnemys", LUAFunction_AroundEnemys },
	{ NULL, NULL }
};

IE_END

#endif