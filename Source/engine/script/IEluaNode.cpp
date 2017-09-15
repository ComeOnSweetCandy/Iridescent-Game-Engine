#define __IE_DLL_EXPORTS__
#include "IEluaNode.h"

IE_BEGIN

int lua_node_create(lua_State* luaSript)
{
	return 1;
}

int lua_node_getPhysicNode(lua_State * LUA)
{
	luaL_checktype(LUA, 1, LUA_TUSERDATA);

	IENode * node = *((IENode**)lua_touserdata(LUA, 1));
	IEPhysicNode * physicNode = node->GetPhysicNode();

	IEPhysicNode ** physicNode_p = (IEPhysicNode**)lua_newuserdata(LUA, sizeof(IEPhysicNode*));
	*physicNode_p = physicNode;

	luaL_getmetatable(LUA, "IEPhysicNode.IEPhysicNode");
	lua_setmetatable(LUA, -2);

	return 1;
}

int lua_node_setPosition(lua_State * luaSript)
{
	luaL_checktype(luaSript, 1, LUA_TUSERDATA);
	luaL_checktype(luaSript, 2, LUA_TNUMBER);
	luaL_checktype(luaSript, 3, LUA_TNUMBER);

	IENode * node = *((IENode**)lua_touserdata(luaSript, 1));
	float position_x = (float)lua_tonumber(luaSript, 2);
	float position_y = (float)lua_tonumber(luaSript, 3);

	node->SetTranslate(position_x, position_y);

	return 0;
}

int lua_node_setAnchor(lua_State * luaSript)
{
	luaL_checktype(luaSript, 1, LUA_TUSERDATA);
	luaL_checktype(luaSript, 2, LUA_TNUMBER);
	luaL_checktype(luaSript, 3, LUA_TNUMBER);

	IENode * node = *((IENode**)lua_touserdata(luaSript, 1));
	float anchor_x = (float)lua_tonumber(luaSript, 2);
	float anchor_y = (float)lua_tonumber(luaSript, 3);

	node->SetAnchor(anchor_x, anchor_y);

	return 0;
}

int lua_node_bindPhysicNode(lua_State * luaSript)
{
	luaL_checktype(luaSript, 1, LUA_TUSERDATA);

	IENode * node = *((IENode**)lua_touserdata(luaSript, 1));
	IEPhysicNode ** p_physicNode = ((IEPhysicNode **)lua_touserdata(luaSript, 2));
	if (p_physicNode)
	{
		IEPhysicNode * physicNode = *p_physicNode;
		node->BindPhysicNode(physicNode);

		const float * translate = node->GetTranslate();
		node->SetTranslate(translate[0], translate[1]);
	}
	else
	{
		node->BindPhysicNode(NULL);
	}

	return 0;
}

int luaopen_node(lua_State *luaSript)
{
	luaL_newmetatable(luaSript, "IENode.IENode");
	lua_pushvalue(luaSript, -1);
	lua_setfield(luaSript, -2, "__index");
	luaL_setfuncs(luaSript, lua_reg_Node_funcs_m, 0);
	luaL_newlib(luaSript, lua_reg_Node_funcs);
	return 1;
}

IE_END