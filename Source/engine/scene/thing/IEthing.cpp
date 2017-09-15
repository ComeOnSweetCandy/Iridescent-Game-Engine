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
	m_LUA = NULL;
}

void IEThing::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEBlock::Initialization();
	IENode::SetDrawMode(false);

	IEThing::SetThingType(thingType);
	IEThing::SetThingID(thingID);
	IEThing::SetOrder(thingOrder);

	//IEThing::SwitchStateTo(0);
	IEThing::SetRelatedOrder(0);

	IEThing::LoadXML();
	IEThing::LoadLUA();
}

IEThing * IEThing::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing * sprite = new IEThing();
	sprite->Initialization(thingType, thingID, thingOrder);
	return sprite;
}

void IEThing::SetThingType(unsigned int thingType)
{
	m_thingType = thingType;
}

unsigned int IEThing::GetThingType()
{
	return m_thingType;
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

void IEThing::ChangeState(const char * stateName)
{
	//��Ҫ������Ϊ���� ������Ϣ �� ��ͼ��Ϣ
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * _stateXML = _xml->FindChild("property")->FindChildWithParameter("state", "stateName", stateName);

	//���ȵ���������Ϣ
	GetPhysicNode()->SetPhysicProperty(_stateXML->FindChild("physic"));

	//������ͼ��
	ChangeAssort(stateName);
}

void IEThing::CheckThing(bool active)
{
	//Ĭ��״̬��
	RereadSelf();
}

void IEThing::LoadXML()
{
	if (m_thingID == 0)
	{
		BindPhysicNode(NULL);
		return;
	}

	//��Ҫ������Ϊ���� ������Ϣ �� ��ͼ��Ϣ ���ﶼ�ǻ�ȡxml��Ϣ
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	m_XML = entrys[m_thingID]._XML;
	const char * _stateName = m_XML->FindChild("property")->FindChild("defaultState")->ValueString();
	IEXml * _stateXML = m_XML->FindChild("property")->FindChildWithParameter("state", "stateName", _stateName);

	//���ȵ���������Ϣ
	IEPhysicNode * physicNode = IEPhysicNode::Create(_stateXML->FindChild("physic"));
	BindPhysicNode(physicNode);

	//��� ����Ĭ����ͼ״̬ ������ͼ��Ϣ
	IEPackerTexture * texture = IEPackerTexture::Create(m_XML->FindChild("texture"));
	ChangeAssort(_stateName);
	ChangeTexture(texture);
}

void IEThing::LoadLUA()
{
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	m_LUA = entrys[m_thingID]._LUA;

	if (!m_LUA)
	{
		m_LUA = luaL_newstate();
		luaL_openlibs(m_LUA);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/thing/", entrys[m_thingID]._ThingName, ".LUA");

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
			luaL_requiref(m_LUA, lua_reg->name, lua_reg->func, 1);
			lua_pop(m_LUA, 1);
		}

		if (luaL_dofile(m_LUA, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find m_LUA file.\n");
		}

		entrys[m_thingID]._LUA = m_LUA;
	}

	//��ȡһЩ�ű�����
	//m_maxState = LUAGetInt(m_LUA, "maxState");

	if (LUAFunctionAllocateFunction(m_LUA, "Init"))
	{
		lua_call(m_LUA, 0, 0);
		//lua_pushnumber(LUA, thingID);
		//IEThing * newThing = *((IEThing **)lua_touserdata(LUA, -1));
		//return newThing;
	}
}

void IEThing::RereadSelf()
{
	//��������ķ���ֵ ���ı���ͼ
	char finalGroupName[256];
	sprintf(finalGroupName, "core");

	//����Ϊ��ȷ��״̬
	ChangeGroup(finalGroupName, 1);
}

IE_END