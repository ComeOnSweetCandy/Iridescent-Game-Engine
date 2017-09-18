#define __IE_DLL_EXPORTS__
#include "IELUACreature.h"

IE_BEGIN

int LUAFunction_AroundEnemys(lua_State * LUA)
{
	luaL_checktype(LUA, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(LUA, 1));
	//int * faceDirection = creature->GetDirection();

	lua_newtable(LUA);//创建一个表格，放在栈顶
	
#define NUMBER 2

	for (int i = 0; i < NUMBER; i++)
	{
		IECreature * newCreature = IECreature::Create(1, 1);
		//newCreature->SetDirection(i, i);

		lua_pushinteger(LUA, i + 1);
		IECreature ** pnewCreature = (IECreature **)lua_newuserdata(LUA, sizeof(IECreature *));
		*pnewCreature = newCreature;
		luaL_setmetatable(LUA, "IECreature.IECreature");
		lua_settable(LUA, -3);
	}
	
	return 1;
}

int LUAFunction_GetFacer(lua_State * LUA)
{
	luaL_checktype(LUA, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(LUA, 1));
	int faceDirection = creature->GetDirection();

	lua_pushinteger(LUA, faceDirection);

	return 1;
}

int LUAInitCreature(lua_State * LUA)
{
	luaL_newmetatable(LUA, "IECreature.IECreature");
	lua_pushvalue(LUA, -1);
	lua_setfield(LUA, -2, "__index");
	luaL_setfuncs(LUA, lua_reg_creature_funcs_m, 0);

	return 1;
}

IE_END