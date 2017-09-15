#define __IE_DLL_EXPORTS__
#include "IEluaPhysicPolygon.h"
#include "../../physic/physicEdge/IEphysicPolygon.h"

#include "../../type/IEstring.h"

IE_BEGIN

int lua_physicPolygon_create(lua_State * LUA)
{
	//luaL_checktype(LUA, 1, LUA_TTABLE);
	//int arrayLength = luaL_len(LUA, -1);

	//IEPhysicPolygonInfo * polygonInfo = new IEPhysicPolygonInfo();
	//polygonInfo->m_physicEdgeType = __edge_polygon__;
	//polygonInfo->m_vertexsNum = arrayLength / 2;
	//polygonInfo->m_vertexs = new IEVector[arrayLength / 2];

	//for (int index = 0; index < arrayLength / 2; index++)
	//{
	//	lua_rawgeti(LUA, 1, index * 2 + 1);
	//	lua_rawgeti(LUA, 1, index * 2 + 2);
	//	float x = lua_tonumber(LUA, -2);
	//	float y = lua_tonumber(LUA, -1);
	//	polygonInfo->m_vertexs[index] = IEVector(x, y);
	//}

	//IEPhysicPolygon ** physicPolygon = (IEPhysicPolygon **)lua_newuserdata(LUA, sizeof(IEPhysicPolygon *));
	//*physicPolygon = IEPhysicPolygon::Create(polygonInfo);

	//luaL_getmetatable(LUA, "IEPhysicPolygon.IEPhysicPolygon");
	//lua_setmetatable(LUA, -2);

	return 1;
}

int luaopen_physicPolygon(lua_State * LUA)
{
	luaL_newmetatable(LUA, "IEPhysicPolygon.IEPhysicPolygon");
	lua_pushvalue(LUA, -1);
	lua_setfield(LUA, -2, "__index");
	luaL_setfuncs(LUA, lua_reg_physicPolygon_funcs_m, 0);
	luaL_newlib(LUA, lua_reg_physicPolygon_funcs);
	return 1;
}

IE_END