/***********************************
* name     : IEluaCollisionTrigger.h
* creater  : cosc
* info     : luaScript script collision trigger
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_COLLISION_TRIGGER__
#define __IE_LUA_COLLISION_TRIGGER__

#include "../trigger/IEcollisionTrigger.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_collisionTrigger_create(lua_State* luaSript);

//extern from physicNode
extern "C" __IE_DLL__ int lua_physicNode_setPosition(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_physicNode_setForward(lua_State * luaSript);

static const luaL_Reg lua_reg_collisionTrigger_funcs[] = {
	{ "Create", lua_collisionTrigger_create },
	{ "SetPosition", lua_physicNode_setPosition },
	{ "SetForward", lua_physicNode_setForward },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_collisionTrigger_funcs_m[] = {
	{ "SetPosition", lua_physicNode_setPosition },
	{ "SetForward", lua_physicNode_setForward },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_collisionTrigger(lua_State * luaSript);

IE_END

#endif