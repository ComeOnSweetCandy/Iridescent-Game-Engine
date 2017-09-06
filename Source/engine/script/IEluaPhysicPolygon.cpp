#define __IE_DLL_EXPORTS__
#include "IEluaPhysicPolygon.h"
#include "../../physic/physicEdge/IEphysicPolygon.h"

#include "../../type/IEstring.h"

IE_BEGIN

int lua_physicPolygon_create(lua_State * luaScript)
{
	//luaL_checktype(luaScript, 1, LUA_TTABLE);
	//int arrayLength = luaL_len(luaScript, -1);

	//IEPhysicPolygonInfo * polygonInfo = new IEPhysicPolygonInfo();
	//polygonInfo->m_physicEdgeType = __edge_polygon__;
	//polygonInfo->m_vertexsNum = arrayLength / 2;
	//polygonInfo->m_vertexs = new IEVector[arrayLength / 2];

	//for (int index = 0; index < arrayLength / 2; index++)
	//{
	//	lua_rawgeti(luaScript, 1, index * 2 + 1);
	//	lua_rawgeti(luaScript, 1, index * 2 + 2);
	//	float x = lua_tonumber(luaScript, -2);
	//	float y = lua_tonumber(luaScript, -1);
	//	polygonInfo->m_vertexs[index] = IEVector(x, y);
	//}

	//IEPhysicPolygon ** physicPolygon = (IEPhysicPolygon **)lua_newuserdata(luaScript, sizeof(IEPhysicPolygon *));
	//*physicPolygon = IEPhysicPolygon::Create(polygonInfo);

	//luaL_getmetatable(luaScript, "IEPhysicPolygon.IEPhysicPolygon");
	//lua_setmetatable(luaScript, -2);

	return 1;
}

int luaopen_physicPolygon(lua_State * luaScript)
{
	luaL_newmetatable(luaScript, "IEPhysicPolygon.IEPhysicPolygon");
	lua_pushvalue(luaScript, -1);
	lua_setfield(luaScript, -2, "__index");
	luaL_setfuncs(luaScript, lua_reg_physicPolygon_funcs_m, 0);
	luaL_newlib(luaScript, lua_reg_physicPolygon_funcs);
	return 1;
}

IE_END