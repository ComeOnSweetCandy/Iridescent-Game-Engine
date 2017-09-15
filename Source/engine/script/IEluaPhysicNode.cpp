#define __IE_DLL_EXPORTS__
#include "IEluaPhysicNode.h"
#include "../../physic/IEphysicNode.h"

IE_BEGIN

int lua_physicNode_create(lua_State* LUA)
{
	luaL_checktype(LUA, 1, LUA_TUSERDATA);
	luaL_checktype(LUA, 2, LUA_TNUMBER);

	IEPhysicEdge * physicEdge = *((IEPhysicEdge**)lua_touserdata(LUA, 1));
	IEPhysicNodeType physicNodeType = (IEPhysicNodeType)lua_tointeger(LUA, 2);

	IEPhysicNode ** physicNode = ((IEPhysicNode**)lua_newuserdata(LUA, sizeof(IEPhysicNode*)));
	*physicNode = IEPhysicNode::Create(physicEdge, physicNodeType);

	luaL_getmetatable(LUA, "IEPhysicNode.IEPhysicNode");
	lua_setmetatable(LUA, -2);

	return 1;
}

int lua_physicNode_setPosition(lua_State* LUA)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(LUA, 1));
	luaL_argcheck(LUA, physicNode != NULL, 1, "invalid user data");

	luaL_checktype(LUA, 2, LUA_TNUMBER);
	luaL_checktype(LUA, 3, LUA_TNUMBER);

	float position_x = (float)lua_tonumber(LUA, 2);
	float position_y = (float)lua_tonumber(LUA, 3);

	physicNode->SetPhysicPosition(position_x, position_y);
	
	return 0;
}

int lua_physicNode_getPosition(lua_State * LUA)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)luaL_checkudata(LUA, 1, "IEPhysicNode.IEPhysicNode"));
	luaL_argcheck(LUA, &physicNode != NULL, 1, "invalid user data");

	IEVector position = physicNode->GetPhysicPosition();

	lua_pushnumber(LUA, position.m_x);
	lua_pushnumber(LUA, position.m_y);

	return 2;
}

int lua_physicNode_setForward(lua_State * LUA)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(LUA, 1));
	luaL_argcheck(LUA, physicNode != NULL, 1, "invalid user data");

	luaL_checktype(LUA, 2, LUA_TNUMBER);
	luaL_checktype(LUA, 3, LUA_TNUMBER);

	float position_x = (float)lua_tonumber(LUA, 2);
	float position_y = (float)lua_tonumber(LUA, 3);

	physicNode->SetForward(position_x, position_y);

	return 1;
}

int lua_physicNode_setSpeed(lua_State * LUA)
{
	IEPhysicNode * physicNode = *((IEPhysicNode**)lua_touserdata(LUA, 1));

	luaL_checktype(LUA, 2, LUA_TNUMBER);

	float speed = (float)lua_tonumber(LUA, 2);

	//physicNode->SetSpeed(speed);

	return 1;
}

int luaopen_physicNode(lua_State *LUA)
{
	luaL_newmetatable(LUA, "IEPhysicNode.IEPhysicNode");
	lua_pushvalue(LUA, -1);
	lua_setfield(LUA, -2, "__index");
	luaL_setfuncs(LUA, lua_reg_physicNode_funcs_m, 0);
	luaL_newlib(LUA, lua_reg_physicNode_funcs);
	return 1;
}

IE_END