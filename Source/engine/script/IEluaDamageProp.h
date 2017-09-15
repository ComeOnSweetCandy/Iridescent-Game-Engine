/***********************************
* name     : IEluaDamageProp.h
* creater  : cosc
* info     : LUA script damage prop
* date     : 2017/3/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_LUA_DAMAGE_PROP__
#define __IE_LUA_DANAGE_PROP__

#include "../atom/prop/IEdamageProp.h"

IE_BEGIN

extern "C" __IE_DLL__ int lua_damageProp_create(lua_State * LUA);

//extern from node
extern "C" __IE_DLL__ int lua_node_setPosition(lua_State * luaSript);

static const luaL_Reg lua_reg_damageProp_funcs[] = {
	{ "Create", lua_damageProp_create },
	{ "SetPosition", lua_node_setPosition },
	{ NULL, NULL },
};

static const luaL_Reg lua_reg_damageProp_funcs_m[] = {
	{ "SetPosition", lua_node_setPosition },
	{ NULL, NULL }
};

extern "C" __IE_DLL__ int luaopen_damageProp(lua_State * LUA);

IE_END

#endif