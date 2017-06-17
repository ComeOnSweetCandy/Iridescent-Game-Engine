#define __IE_DLL_EXPORTS__
#include "IEluaPhysicNode.h"
#include "../../physic/IEphysicNode.h"

IE_BEGIN

int lua_physicNode_create(lua_State* luaScript)
{
	luaL_checktype(luaScript, 1, LUA_TUSERDATA);
	luaL_checktype(luaScript, 2, LUA_TNUMBER);

	IEPhysicEdge * physicEdge = *((IEPhysicEdge**)lua_touserdata(luaScript, 1));
	IEPhysicNodeType physicNodeType = (IEPhysicNodeType)lua_tointeger(luaScript, 2);

	IEPhysicNode ** physicNode = ((IEPhysicNode**)lua_newuserdata(luaScript, sizeof(IEPhysicNode*)));
	*physicNode = IEPhysicNode::Create(physicEdge, physicNodeType);

	luaL_getmetatable(luaScript, "IEPhysicNode.IEPhysicNode");
	lua_setmetatable(luaScript, -2);

	return 1;
}

int lua_physicNode_setPosition(lua_State* luaScript)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(luaScript, 1));
	luaL_argcheck(luaScript, physicNode != NULL, 1, "invalid user data");

	luaL_checktype(luaScript, 2, LUA_TNUMBER);
	luaL_checktype(luaScript, 3, LUA_TNUMBER);

	float position_x = (float)lua_tonumber(luaScript, 2);
	float position_y = (float)lua_tonumber(luaScript, 3);

	physicNode->SetPhysicPosition(position_x, position_y);
	
	return 0;
}

int lua_physicNode_getPosition(lua_State * luaScript)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)luaL_checkudata(luaScript, 1, "IEPhysicNode.IEPhysicNode"));
	luaL_argcheck(luaScript, &physicNode != NULL, 1, "invalid user data");

	IEVector position = physicNode->GetPhysicPosition();

	lua_pushnumber(luaScript, position.m_x);
	lua_pushnumber(luaScript, position.m_y);

	return 2;
}

int lua_physicNode_setForward(lua_State * luaScript)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(luaScript, 1));
	luaL_argcheck(luaScript, physicNode != NULL, 1, "invalid user data");

	luaL_checktype(luaScript, 2, LUA_TNUMBER);
	luaL_checktype(luaScript, 3, LUA_TNUMBER);

	float position_x = (float)lua_tonumber(luaScript, 2);
	float position_y = (float)lua_tonumber(luaScript, 3);

	physicNode->SetForward(position_x, position_y);

	return 1;
}

int lua_physicNode_setSpeed(lua_State * luaScript)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(luaScript, 1));

	luaL_checktype(luaScript, 2, LUA_TNUMBER);

	float speed = (float)lua_tonumber(luaScript, 2);

	//physicNode->SetSpeed(speed);

	return 1;
}

int luaopen_physicNode(lua_State *luaScript)
{
	luaL_newmetatable(luaScript, "IEPhysicNode.IEPhysicNode");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_physicNode_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_physicNode_funcs);
	return 1;
}

IE_END