///***********************************
//* name     : IEluaProp.h
//* creater  : cosc
//* info     : LUA script prop
//* date     : 2017/3/27
//* version  : 1.0
//* remark   : none
//************************************/
//
//#ifndef __IE_LUA_PROP__
//#define __IE_LUA_PROP__
//
//#include "../atom/IEprop.h"
//
//IE_BEGIN
//
//extern "C" __IE_DLL__ int lua_prop_create(lua_State * LUA);
//extern "C" __IE_DLL__ int lua_prop_createFire(lua_State * LUA);
//
//extern "C" __IE_DLL__ int lua_prop_bindTrigger(lua_State * LUA);
//
//static const luaL_Reg lua_reg_Prop_funcs[] = {
//	{ "Create", lua_prop_create },
//	{ "CreateFire", lua_prop_createFire },
//	{ "BindTrigger", lua_prop_bindTrigger },
//	{ NULL, NULL },
//};
//
//static const luaL_Reg lua_reg_Prop_funcs_m[] = {
//	{ "BindTrigger", lua_prop_bindTrigger },
//	{ NULL, NULL }
//};
//
//extern "C" __IE_DLL__ int luaopen_prop(lua_State * LUA);
//
//IE_END
//
//#endif