/***********************************
* name     : IEluaCreature.h
* creater  : cosc
* info     : luaScript script node
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_Creature__
#define __IE_LUA_Creature__

#include "../atom/creature/IECreature.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_creature_create(lua_State * lua);

extern "C" __IE_DLL__ int lua_creature_getFacer(lua_State * lua);
extern "C" __IE_DLL__ int lua_creature_cure(lua_State * lua);
extern "C" __IE_DLL__ int lua_follow_enemy(lua_State * lua);

extern "C" __IE_DLL__ int lua_creature_getSelf(lua_State * lua);



static const luaL_Reg lua_reg_creature_funcs[] = {
	{ "Create", lua_creature_create },
	{ "GetFacer", lua_creature_getFacer },
	{ "Cure", lua_creature_cure },
	{ "FollowEnemy", lua_follow_enemy},
	{ "GetSelf", lua_creature_getSelf },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_creature_funcs_m[] = {
	{ "GetFacer", lua_creature_getFacer },
	{ "Cure", lua_creature_cure },
	{ "FollowEnemy", lua_follow_enemy },
	{ "GetSelf", lua_creature_getSelf },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_creature(lua_State *luaSript);

IE_END

#endif