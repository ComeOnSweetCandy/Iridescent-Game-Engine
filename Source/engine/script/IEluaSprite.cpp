#define __IE_DLL_EXPORTS__
#include "IEluaSprite.h"

IE_BEGIN

int lua_sprite_changeTexture(lua_State * luaSript)
{
	return 0;
}

int lua_sprite_changeTextureOnce(lua_State * luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TUSERDATA);
	luaL_checktype(luaScript, 2, LUA_TSTRING);

	IESprite * sprite = *((IESprite**)lua_touserdata(luaScript, 1));
	const char * textureNmae = (const char *)lua_tostring(luaScript, 2);
	sprite->ChangeTextureOnce(textureNmae);
	
	return 0;
}

int luaopen_node(lua_State *luaSript)
{
	luaL_newmetatable(luaSript, "IESprite.IESprite");
	lua_pushvalue(luaSript, -1);
	lua_setfield(luaSript, -2, "__index");
	luaL_setfuncs(luaSript, lua_reg_Sprite_funcs_m, 0);
	luaL_newlib(luaSript, lua_reg_Sprite_funcs);
	return 1;
}

IE_END