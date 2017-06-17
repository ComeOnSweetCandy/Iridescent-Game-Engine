/***********************************
* name     : IEluaSprite.h
* creater  : cosc
* info     : luaScript script node
* date     : 2017/5/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_SPRITE__
#define __IE_LUA_SPRITE__

#include "../../core/element/IEsprite.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_sprite_changeTexture(lua_State * luaSript);
extern "C" __IE_DLL__ int lua_sprite_changeTextureOnce(lua_State * luaScript);

static const luaL_Reg lua_reg_Sprite_funcs[] = {
	{ "ChangeTexture", lua_sprite_changeTexture },
	{ "ChangeTextureOnce", lua_sprite_changeTextureOnce },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_Sprite_funcs_m[] = {
	{ "ChangeTexture", lua_sprite_changeTexture },
	{ "ChangeTextureOnce", lua_sprite_changeTextureOnce },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_sprite(lua_State * luaSript);

IE_END

#endif