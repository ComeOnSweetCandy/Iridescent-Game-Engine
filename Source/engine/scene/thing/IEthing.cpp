#define __IE_DLL_EXPORTS__
#include "IEthing.h"

#include "IEThingList.h"
#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicCircle.h"
#include "../../script/IEluaPhysicNode.h"
#include "../../script/IEluaThing.h"

IE_BEGIN

IEThing::IEThing()
{
	m_thingID = 0;
	m_order = 0;
	m_relatedOrder = 0;
	m_express = true;

	m_maxState = 1;
	m_curState = 0;
}

IEThing::~IEThing()
{
	m_script = NULL;
}

void IEThing::Initialization(unsigned int thingID, unsigned int thingOrder)
{
	IENode::SetDrawMode(false);
	IEThing::SetThingID(thingID);
	IEThing::SetOrder(thingOrder);

	IEThing::SwitchStateTo(0);
	IEThing::SetRelatedOrder(0);

	IEThing::LoadXML();
	IEThing::LoadLUA();
}

IEThing * IEThing::Create(unsigned int thingID, unsigned int thingOrder)
{
	IEThing * sprite = new IEThing();
	sprite->Initialization(thingID, thingOrder);
	return sprite;
}

void IEThing::SetThingID(unsigned int adorningID)
{
	m_thingID = adorningID;
}

unsigned int IEThing::GetThingID()
{
	return m_thingID;
}

void IEThing::SetOrder(unsigned int order)
{
	m_order = order;
}

unsigned int IEThing::GetOrder()
{
	return m_order;
}

void IEThing::SetRelatedOrder(unsigned int relatedCreatedOrder)
{
	m_relatedOrder = relatedCreatedOrder;
}

unsigned int IEThing::GetRelatedOrder()
{
	return m_relatedOrder;
}

void IEThing::SetLocations(int blockLocationX, int blockLocationY, int tinyLocationX, int tinyLocationY)
{
	m_locations[0] = blockLocationX;
	m_locations[1] = blockLocationY;
	m_locations[2] = tinyLocationX;
	m_locations[3] = tinyLocationY;
}

int * IEThing::GetLocations()
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

void IEThing::SwitchStateTo(unsigned int stateIndex)
{
	//需要调整的为两项 物理信息 和 贴图信息
	m_curState = stateIndex;

	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * _stateXML = _xml->FindChild("state", m_curState);

	//首先调整物理信息
	IEPhysicNode * physicNode = IEPhysicNode::Create(_stateXML->FindChild("physic"));
	BindPhysicNode(physicNode);

	//其次调整贴图信息
	IEPackerTexture * texture = IEPackerTexture::Create(_stateXML->FindChild("texture"));
	ChangeTexture(texture);

	//下面是以往旧的脚本信息
	//if (!m_maxState)
	//{
	//	return;
	//}

	//m_curState = m_curState + 1;
	//if (m_curState >= m_maxState)
	//{
	//	m_curState = 0;
	//}

	//if (AllocateLuaFunction(m_script, "ChangeState"))
	//{
	//	lua_pushnumber(m_script, m_curState);
	//	lua_call(m_script, 1, 0);
	//}

	////两者应当互不影响
	//ChangeState(1);
	//ChangeGroup("normal");
}

void IEThing::LoadXML()
{
	if (m_thingID == 0)
	{
		BindPhysicNode(NULL);
		return;
	}

	//获取当前状态下的XML
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * _stateXML = _xml->FindChild("state", m_curState);

	//设定该thing的物理状态
	IEPhysicNode * physicNode = IEPhysicNode::Create(_stateXML->FindChild("physic"));
	BindPhysicNode(physicNode);

	//读取该thing的贴图
	IEPackerTexture * texture = IEPackerTexture::Create(_stateXML->FindChild("texture"));
	ChangeTexture(texture);
	ChangeGroup("normal");
}

void IEThing::LoadLUA()
{
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	m_script = entrys[m_thingID]._LUA;

	if (!m_script)
	{
		m_script = luaL_newstate();
		luaL_openlibs(m_script);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/thing/", entrys[m_thingID]._ThingName, ".lua");

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
			luaL_requiref(m_script, lua_reg->name, lua_reg->func, 1);
			lua_pop(m_script, 1);
		}

		if (luaL_dofile(m_script, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find m_script file.\n");
		}

		entrys[m_thingID]._LUA = m_script;
	}

	//读取一些脚本变量
	//m_maxState = GetLuaIntElement(m_script, "maxState");

	if (AllocateLuaFunction(m_script, "Init"))
	{
		lua_call(m_script, 0, 0);
		//lua_pushnumber(luaScript, thingID);
		//IEThing * newThing = *((IEThing **)lua_touserdata(luaScript, -1));
		//return newThing;
	}
}

IE_END