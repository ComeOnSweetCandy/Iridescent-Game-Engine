/***********************************
* name     : IEluaPhysicNode.h
* creater  : cosc
* info     : luaScript script physic node
* date     : 2017/3/22
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_PHYSIC_NODE__
#define __IE_LUA_PHYSIC_NODE__

#include "../../global/IEstdafx.h"

IE_BEGIN

class IEPhysicNode;

extern "C" __IE_DLL__ int lua_physicNode_create(lua_State* luaSript);

extern "C" __IE_DLL__ int lua_physicNode_setPosition(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_physicNode_getPosition(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_physicNode_setForward(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_physicNode_setSpeed(lua_State * luaSript);

static const luaL_Reg lua_reg_physicNode_funcs[] = {
	{ "Create", lua_physicNode_create },
	{ "SetPosition", lua_physicNode_setPosition },
	{ "GetPosition", lua_physicNode_getPosition },
	{ "SetForward", lua_physicNode_setForward },
	{ "SetSpeed", lua_physicNode_setSpeed },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_physicNode_funcs_m[] = {
	{ "SetPosition", lua_physicNode_setPosition },
	{ "GetPosition", lua_physicNode_getPosition },
	{ "SetForward", lua_physicNode_setForward },
	{ "SetSpeed", lua_physicNode_setSpeed },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_physicNode(lua_State *luaSript);

IE_END

#endif