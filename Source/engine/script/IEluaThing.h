/***********************************
* name     : IEluaThing.h
* creater  : cosc
* info     : LUA script thing
* date     : 2017/4/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_THING__
#define __IE_LUA_THING__

#include "../scene/thing/IEthing.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_thing_create(lua_State * LUA);

extern "C" __IE_DLL__ int lua_node_bindPhysicNode(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_sprite_changeTextureOnce(lua_State * LUA);

static const luaL_Reg lua_reg_Thing_funcs[] = {
	{ "Create", lua_thing_create },
	{ "BindPhysicNode", lua_node_bindPhysicNode },						//IEluaNode
	{ "ChangeTextureOnce", lua_sprite_changeTextureOnce },				//IEluaSprite
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_Thing_funcs_m[] = {
	{ "BindPhysicNode", lua_node_bindPhysicNode },						//IEluaNode
	{ "ChangeTextureOnce", lua_sprite_changeTextureOnce },				//IEluaSprite
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_thing(lua_State * LUA);

IE_END

#endif