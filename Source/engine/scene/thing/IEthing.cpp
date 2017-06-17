#define __IE_DLL_EXPORTS__
#include "IEthing.h"

#include "IEthingsInfoManager.h"
#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicCircle.h"
#include "../../script/IEluaPhysicNode.h"
#include "../../script/IEluaThing.h"

IE_BEGIN

IEThing::IEThing()
{
	m_tinyGridPosition = IEGrid(0, 0);
	m_unitPixels = 32;
	m_thingID = 0;
	m_express = true;

	m_maxState = 0;
	m_curState = 0;

	m_relatedCreatedOrder = 0;
}

IEThing::~IEThing()
{
	m_luaScript = NULL;
}

void IEThing::Initialization(unsigned int thingID)
{
	IESprite::Initialization(NULL);
	IENode::SetDrawMode(false);

	SetThingID(thingID);
	LoadScript();
}

IEThing * IEThing::Create(unsigned int thingID)
{
	IEThing * sprite = new IEThing();
	sprite->Initialization(thingID);
	return sprite;
}

void IEThing::Reload(unsigned int thingID)
{
	SetThingID(thingID);
}

void IEThing::LoadScript()
{
	IEAdorningInfo * adorningsInfo = IEAdorningsInfoManager::Share()->GetAdorningsInfoList();
	m_luaScript = adorningsInfo[m_thingID]._LuaScript;

	if (!m_luaScript)
	{
		m_luaScript = luaL_newstate();
		luaL_openlibs(m_luaScript);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/thing/", adorningsInfo[m_thingID]._ThingName, ".lua");

		luaL_Reg lua_reg_libs[] =
		{
			{ "base", luaopen_base },
			{ "IEPhysicPolygon", luaopen_physicPolygon },
			{ "IEPhysicCircle", luaopen_physicCircle },
			{ "IEPhysicNode", luaopen_physicNode },
			{ "IEThing", luaopen_thing },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(m_luaScript, lua_reg->name, lua_reg->func, 1);
			lua_pop(m_luaScript, 1);
		}

		if (luaL_dofile(m_luaScript, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find m_luaScript file.\n");
		}

		adorningsInfo[m_thingID]._LuaScript = m_luaScript;
	}

	//读取一些脚本变量
	m_maxState = GetLuaIntElement(m_luaScript, "maxState");

	if (AllocateLuaFunction("Init"))
	{
		lua_call(m_luaScript, 0, 0);
	}
}

bool IEThing::CheckTinyMask(unsigned short tinyMask, int number)
{
	int result = tinyMask << (16 - number) >> (16 - number);
	bool res = result == 0 ? false : true;
	return res;
}

void IEThing::DrawNode()
{
	IESprite::DrawNode();
}

void IEThing::SetTinyGridPosition(int x, int y)
{
	m_tinyGridPosition = IEGrid(x, y);
}

IEGrid IEThing::GetTinyGridPosition()
{
	return m_tinyGridPosition;
}

void IEThing::SetThingID(unsigned int adorningID)
{
	m_thingID = adorningID;
}

unsigned int IEThing::GetThingID()
{
	return m_thingID;
}

bool IEThing::AllocateLuaFunction(const char * functionName)
{
	if (lua_getglobal(m_luaScript, functionName))
	{
		SetLuaUserdataElement(m_luaScript, "self", "IEThing.IEThing", this);

		return true;
	}
	else
	{
		lua_pop(m_luaScript, -1);

		return false;
	}
}

void IEThing::SwitchState()
{
	if (!m_maxState)
	{
		return;
	}

	m_curState = m_curState + 1;
	if (m_curState >= m_maxState)
	{
		m_curState = 0;
	}

	if (AllocateLuaFunction("ChangeState"))
	{
		lua_pushnumber(m_luaScript, m_curState);
		lua_call(m_luaScript, 1, 0);
	}
}

void IEThing::ChangeThingID(unsigned thingID)
{

}

void IEThing::SetRelatedCreatedOrder(unsigned int relatedCreatedOrder)
{
	m_relatedCreatedOrder = relatedCreatedOrder;
}

unsigned int IEThing::GetRelatedCreatedOrder()
{
	return m_relatedCreatedOrder;
}

void IEThing::SetThingLocations(int blockLocationX, int blockLocationY, int tinyLocationX, int tinyLocationY)
{
	m_locations[0] = blockLocationX;
	m_locations[1] = blockLocationY;
	m_locations[2] = tinyLocationX;
	m_locations[3] = tinyLocationY;
}

int * IEThing::GetThingLocations()
{
	return m_locations;
}

void IEThing::SetExpress(bool express)
{
	m_express = express;
}

bool IEThing::GetExpress()
{
	return m_express;
}

IE_END