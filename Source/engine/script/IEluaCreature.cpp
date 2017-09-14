#define __IE_DLL_EXPORTS__
#include "IEluaCreature.h"

IE_BEGIN

int lua_creature_create(lua_State* lua)
{
	return 1;
}

int lua_creature_getSelf(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));
	int * faceDirection = creature->GetDirection();

	//lua_newtable(lua);//����һ����񣬷���ջ��
	//lua_pushinteger(lua, 1);//ѹ��key
	//lua_pushinteger(lua, 66);//ѹ��value
	//lua_settable(lua, -3);//����key,value�������õ�table����ȥ

	//lua_pushinteger(lua, 2);//ѹ��key
	//lua_pushinteger(lua, 166);//ѹ��value
	//lua_settable(lua, -3);//����key,value�������õ�table����ȥ

	//lua_pushinteger(lua, 3);//ѹ��key
	//lua_pushinteger(lua, 1166);//ѹ��value
	//lua_settable(lua, -3);//����key,value�������õ�table����ȥ

	//return 1;//��ջ�����ھ�һ��table.�������������ˡ�




	lua_newtable(lua);//����һ����񣬷���ջ��

	for (int i = 0; i < 3; i++)
	{
		IECreature * newCreature = IECreature::Create(1, 1);
		newCreature->SetDirection(i, i);

		lua_pushinteger(lua, i + 1);
		lua_pushlightuserdata(lua, newCreature);
		lua_settable(lua, -3);

		

		//IECreature * newCreature = IECreature::Create(1, 1);
		//newCreature->SetDirection(i, i);

		//IECreature ** pnewCreature = (IECreature **)lua_newuserdata(lua, sizeof(IECreature *));
		//*pnewCreature = newCreature;
		//luaL_getmetatable(lua, "IECreature.IECreature");
		//lua_setmetatable(lua, -2);
	}
	
	return 1;
}

int lua_creature_getFacer(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));
	int * faceDirection = creature->GetDirection();

	lua_pushinteger(lua, faceDirection[0]);
	lua_pushinteger(lua, faceDirection[1]);

	return 2;
}

int lua_creature_cure(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);
	luaL_checktype(lua, 2, LUA_TNUMBER);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));
	int cureValue = (int)lua_tointeger(lua, 2);

	creature->Cured(cureValue);

	return 0;
}

int lua_follow_enemy(lua_State * lua)
{
	luaL_checktype(lua, 1, LUA_TUSERDATA);

	IECreature * creature = *((IECreature**)lua_touserdata(lua, 1));

	//creature->FollowEnemy();

	return 0;
}

int luaopen_creature(lua_State *lua)
{
	luaL_newmetatable(lua, "IECreature.IECreature");
	lua_pushvalue(lua, -1);
	lua_setfield(lua, -2, "__index");
	luaL_setfuncs(lua, lua_reg_creature_funcs_m, 0);
	luaL_newlib(lua, lua_reg_creature_funcs);
	return 1;
}

IE_END