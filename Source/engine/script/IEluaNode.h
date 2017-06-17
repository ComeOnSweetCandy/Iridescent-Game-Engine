/***********************************
* name     : IEluaNode.h
* creater  : cosc
* info     : luaScript script node
* date     : 2017/3/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_NODE__
#define __IE_LUA_NODE__

#include "../../core/IEnode.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_node_create(lua_State* luaSript);

extern "C" __IE_DLL__ int lua_node_getPhysicNode(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_node_setPosition(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_node_setAnchor(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_node_bindPhysicNode(lua_State * luaSript);

static const luaL_Reg lua_reg_Node_funcs[] = {
	{ "Create", lua_node_create },
	{ "GetPhysicNode", lua_node_getPhysicNode },
	{ "SetPosition", lua_node_setPosition },
	{ "SetAnchor", lua_node_setAnchor },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_Node_funcs_m[] = {
	{ "GetPhysicNode", lua_node_getPhysicNode },
	{ "SetPosition", lua_node_setPosition },
	{ "SetAnchor", lua_node_setAnchor },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_node(lua_State *luaSript);

IE_END

#endif