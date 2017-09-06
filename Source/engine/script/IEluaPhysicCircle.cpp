#define __IE_DLL_EXPORTS__
#include "IEluaPhysicCircle.h"
#include "../../physic/physicEdge/IEphysicCircle.h"

IE_BEGIN

int lua_physicCircle_create(lua_State* luaSript)
{
	//luaL_checktype(luaSript, 1, LUA_TNUMBER);
	//luaL_checktype(luaSript, 2, LUA_TNUMBER);

	//float physicCircleRadius = (float)lua_tonumber(luaSript, 1);
	//int physicCircleVertexsCount = (int)lua_tointeger(luaSript, 2);

	//IEPhysicCircleInfo * circleInfo = new IEPhysicCircleInfo();
	//circleInfo->m_physicEdgeType = __edge_circle__;
	//circleInfo->m_radius = physicCircleRadius;
	//circleInfo->m_vertexsNum = physicCircleVertexsCount;

	//IEPhysicCircle ** physicCircle = (IEPhysicCircle**)lua_newuserdata(luaSript, sizeof(IEPhysicCircle*));
	//*physicCircle = IEPhysicCircle::Create(circleInfo);

	//luaL_getmetatable(luaSript, "IEPhysicCircle.IEPhysicCircle");
	//lua_setmetatable(luaSript, -2);

	return 1;
}

int lua_physicCircle_setRadius(lua_State* luaSript)
{
	return 1;
}

int lua_physicCircle_getRadius(lua_State* luaSript)
{
	return 1;
}

int luaopen_physicCircle(lua_State *luaSript)
{
	luaL_newmetatable(luaSript, "IEPhysicCircle.IEPhysicCircle");
	lua_pushvalue(luaSript, -1);
	lua_setfield(luaSript, -2, "__index");
	luaL_setfuncs(luaSript, lua_reg_physicCircle_funcs_m, 0);
	luaL_newlib(luaSript, lua_reg_physicCircle_funcs);
	return 1;
}

IE_END