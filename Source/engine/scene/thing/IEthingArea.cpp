#define __IE_DLL_EXPORTS__
#include "IEthingArea.h"

#include "../path/IEPathArea.h"

#include "../../script/IEluaPhysicPolygon.h"
#include "../../script/IEluaPhysicNode.h"
#include "../../script/IEluaThing.h"

#include "../../../control/IEmouse.h"

IE_BEGIN

IEThingArea::IEThingArea()
{
	m_readyThingID = 0;
	m_curOrder = 1;
	m_regularization = true;
}

IEThingArea::~IEThingArea()
{

}

void IEThingArea::Initialization(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEArea::Initialization(map, halfViewBlocks, blockSize);

	m_thingsInfo = IEAdorningsInfoManager::Share()->GetAdorningsInfoList();


	//m_suspensionThing = IESprite::Create("bucket/body.png");
	//m_suspensionThing->SetTranslate(1.0f, 1.0f);
	//m_suspensionThing->SetDisplay(false);
	//IENode::AddChild(m_suspensionThing);
}

IEThingArea * IEThingArea::Create(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEThingArea * object = new IEThingArea();
	object->Initialization(map, halfViewBlocks, blockSize);
	return object;
}

IEThing * IEThingArea::LoadChild(unsigned m_thingID, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	if (m_thingID == 0)
	{
		return NULL;
	}

	IEThing * thing = IEThing::Create(m_thingID);
	thing->ChangeTexture((IEString(m_thingsInfo[m_thingID]._ThingName) + "/body.png").GetString());
	m_map->BuildPath(thing->GetPhysicNode());

	AddThing(thing, locationX, locationY, tinyLocationX, tinyLocationY);
	thing->SetThingLocations(locationX, locationY, tinyLocationX, tinyLocationY);

	for (int index = 0; index < m_thingsInfo[m_thingID]._OccupyCount; index++)
	{
		int baseLocationX = locationX + m_thingsInfo[m_thingID]._OccupyInfo[index]._X;
		int baseLocationY = locationY + m_thingsInfo[m_thingID]._OccupyInfo[index]._Y;
		unsigned short tinyMark = m_thingsInfo[m_thingID]._OccupyInfo[index]._Mask;

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				int tinyLocation_x = tinyLocationX + x;
				int tinyLocation_y = tinyLocationY + y;

				int locationOffset_x = tinyLocation_x / 4;
				int locationOffset_y = tinyLocation_y / 4;

				tinyLocation_x = tinyLocation_x % 4;
				tinyLocation_y = tinyLocation_y % 4;

				unsigned short zer = 1;
				zer = zer << (15 - x * 4 - y);
				if (tinyMark & zer)
				{
					HoldThing(thing, baseLocationX + locationOffset_x, baseLocationY + locationOffset_y, tinyLocation_x, tinyLocation_y);
				}
			}
		}
	}

	return thing;
}

IEThing * IEThingArea::AddChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	if (m_readyThingID == 0)
	{
		return NULL;
	}

	if (!AllowChild(locationX, locationY, tinyLocationX, tinyLocationY))
	{
		return NULL;
	}

	//加入修改缓存
	m_thingAlter = new IEThingAlter();
	m_thingAlter->_X = locationX;
	m_thingAlter->_Y = locationY;
	m_thingAlter->_TinyX = tinyLocationX;
	m_thingAlter->_TinyY = tinyLocationY;
	m_thingAlter->_ThingID = m_readyThingID;
	m_thingAlter->_Order = m_curOrder++;
	m_thingAlter->_ExtraOrder = 0;
	m_thingAlter->_OperaType = __IE_THING_ALTER_OPERA_ADD__;
	m_alters->Push(m_thingAlter);

	//IEThing * thing = CreateThing(m_readyThingID);
	IEThing * thing = IEThing::Create(m_readyThingID);
	thing->ChangeTexture((IEString(m_thingsInfo[m_readyThingID]._ThingName) + "/body.png").GetString());
	m_map->BuildPath(thing->GetPhysicNode());

	AddThing(thing, locationX, locationY, tinyLocationX, tinyLocationY);
	thing->SetThingLocations(locationX, locationY, tinyLocationX, tinyLocationY);

	for (int index = 0; index < m_thingsInfo[m_readyThingID]._OccupyCount; index++)
	{
		int baseLocationX = locationX + m_thingsInfo[m_readyThingID]._OccupyInfo[index]._X;
		int baseLocationY = locationY + m_thingsInfo[m_readyThingID]._OccupyInfo[index]._Y;
		unsigned short tinyMark = m_thingsInfo[m_readyThingID]._OccupyInfo[index]._Mask;

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				int tinyLocation_x = tinyLocationX + x;
				int tinyLocation_y = tinyLocationY + y;

				int locationOffset_x = tinyLocation_x / 4;
				int locationOffset_y = tinyLocation_y / 4;

				tinyLocation_x = tinyLocation_x % 4;
				tinyLocation_y = tinyLocation_y % 4;

				unsigned short zer = 1;
				zer = zer << (15 - x * 4 - y);
				if (tinyMark & zer)
				{
					HoldThing(thing, baseLocationX + locationOffset_x, baseLocationY + locationOffset_y, tinyLocation_x, tinyLocation_y);
				}
			}
		}
	}

	return thing;
}

void IEThingArea::RemoveChild()
{
	IEThing * thing = FindThingByOrder(m_choosenThingOrder);
	IEThingChunk * parent = (IEThingChunk *)(thing->GetParentNode());

	unsigned int thingID = thing->GetThingID();
	int * locations = thing->GetThingLocations();

	if (thing)
	{
		m_thingAlter = new IEThingAlter();
		m_thingAlter->_X = locations[0];
		m_thingAlter->_Y = locations[1];
		m_thingAlter->_TinyX = locations[2];
		m_thingAlter->_TinyY = locations[3];
		m_thingAlter->_ThingID = 0;
		m_thingAlter->_ExtraOrder = thingID;
		m_thingAlter->_OperaType = __IE_THING_ALTER_OPERA_DEL__;
		m_thingAlter->_ExtraOrder = thing->GetRelatedCreatedOrder();
		m_alters->Pop(m_thingAlter);

		RemoveThing(locations[0], locations[1], locations[2], locations[3]);

		for (int index = 0; index < m_thingsInfo[thingID]._OccupyCount; index++)
		{
			unsigned short tinyMark = m_thingsInfo[thingID]._OccupyInfo[index]._Mask;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					int tinyLocation_x = locations[2] + x;
					int tinyLocation_y = locations[3] + y;

					int locationOffset_x = tinyLocation_x / 4;
					int locationOffset_y = tinyLocation_y / 4;

					tinyLocation_x = tinyLocation_x % 4;
					tinyLocation_y = tinyLocation_y % 4;

					unsigned short zer = 1;
					zer = zer << (15 - x * 4 - y);
					if (tinyMark & zer)
					{
						EraseThing(locations[0] + m_thingsInfo[m_readyThingID]._OccupyInfo[index]._X + locationOffset_x, locations[1] + m_thingsInfo[m_readyThingID]._OccupyInfo[index]._Y + locationOffset_y, tinyLocation_x, tinyLocation_y);
					}
				}
			}
		}
	}
}

IEThing * IEThingArea::ChooseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	return NULL;
	//IEGrid chunkLocation;
	//IEGrid explicitBlockLocation;

	//LocationTranslate(IEGrid(locationX, locationY), chunkLocation, explicitBlockLocation);
	//IEGrid offset = chunkLocation - m_centerChunkLocation;

	//if (!legalRange(offset))
	//{
	//	return NULL;
	//}

	//IEThingChunk * chunk = (IEThingChunk *)m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
	//IEThing * thing = chunk->GetChild(explicitBlockLocation.m_x, explicitBlockLocation.m_y, tinyLocationX, tinyLocationY);

	//return thing;
}

void IEThingArea::RollbackControll()
{
	int count = m_alters->Count();
	if (count == 0)
	{
		return;
	}

	IEObject * object = m_alters->PopTop();
	IEThingAlter * controll = (IEThingAlter *)object;
}

void IEThingArea::RollbackAllControlls()
{
	int count = m_alters->Count();
	if (count == 0)
	{
		return;
	}

	while (IEObject * object = m_alters->PopTop())
	{
		IEThingAlter * controll = (IEThingAlter *)object;
	}
}

void IEThingArea::SetReadyThing(unsigned int thingID)
{
	m_readyThingID = thingID;

	if (m_readyThingID)
	{
		IEString s = IEString(m_thingsInfo[thingID]._ThingName) + "/body.png";
		m_suspensionThing->ChangeTexture(s.GetString());
		m_suspensionThing->SetDisplay(true);
	}
	else
	{
		m_suspensionThing->SetDisplay(false);
	}
}

void IEThingArea::MouseSuspension(float positionX, float positionY)
{
	//首先计算鼠标所指向的格子和小格子
	IEGrid mouseLocation = IEGrid(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY);

	//根据switch来决定是否归整化
	if (m_regularization)
	{
		m_mouseTinyLocation = 0;
	}
	else
	{
		m_mouseTinyLocation = IEVector(positionX - (float)mouseLocation.m_x, positionY - (float)mouseLocation.m_y) / 0.25f;
	}

	if (m_mouseTinyLocation.m_x == 4)
	{
		m_mouseTinyLocation.m_x = 0;
		m_mouseTinyLocation.m_x = m_mouseTinyLocation.m_x + 1;
	}
	if (m_mouseTinyLocation.m_y == 4)
	{
		m_mouseTinyLocation.m_y = 0;
		m_mouseTinyLocation.m_y = m_mouseTinyLocation.m_y + 1;
	}

	if (m_readyThingID)
	{
		//选择了一个 thingID 检测是否可行
		bool result = AllowChild(m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y, m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y);

		if (result)
		{
			m_suspensionThing->SetBackColor(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			m_suspensionThing->SetBackColor(1.0f, 0.0f, 0.0f, 0.7f);
		}
		m_suspensionThing->SetTranslate(m_mouseTinyLocation.m_x + m_mouseTinyLocation.m_x * 0.25f, m_mouseTinyLocation.m_y + m_mouseTinyLocation.m_y * 0.25f);
	}
	else
	{
		//没有选择 thingID 亮起待选择
		IEThing * thing = ChooseThing(m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y, m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y);
	}
}

void IEThingArea::MouseLButtonTouch()
{
	//if (m_readyThingID)
	//{
	//	AddChild(m_mouseLocation.m_x, m_mouseLocation.m_y, m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y);
	//}
	//else
	//{
	//	IEThing * thing = ChooseThing(m_mouseLocation.m_x, m_mouseLocation.m_y, m_mouseTinyLocation.m_x, m_mouseTinyLocation.m_y);
	//	m_choosenThingOrder = thing->GetOrder();
	//}
}

void IEThingArea::MouseRButtonTouch()
{
	m_readyThingID = 0;
	m_choosenThingOrder = 0;

	m_suspensionThing->SetDisplay(false);
}

void IEThingArea::LoadChunk(int blockX, int blockY)
{
	m_map->LoadThingChunk(blockX, blockY);
}

void IEThingArea::LoadChild(int blockX, int blockY, IEThingBlockFormat * alters)
{
	if (!alters)
	{
		return;
	}

	unsigned int size = m_chunkLength * m_chunkLength;
	for (unsigned int index = 0; index < size; index++)
	{
		if (alters[index]._ThingID)
		{
			IEThing * things = LoadChild(alters[index]._ThingID, alters[index]._X, alters[index]._Y, alters[index]._TinyX, alters[index]._TinyY);
			things->SetRelatedCreatedOrder(alters[index]._ThingID);
		}
	}
}

IEThing * IEThingArea::CreateThing(unsigned thingID)
{
	IEAdorningInfo * adorningsInfo = IEAdorningsInfoManager::Share()->GetAdorningsInfoList();
	lua_State * luaScript = adorningsInfo[thingID]._LuaScript;

	if (!luaScript)
	{
		luaScript = luaL_newstate();
		luaL_openlibs(luaScript);

		char scriptName[64];
		sprintf(scriptName, "%s%s%s", "../Debug/data/script/adorning/", adorningsInfo[thingID]._ThingName, ".lua");

		luaL_Reg lua_reg_libs[] =
		{
			{ "base", luaopen_base },
			{ "IEPhysicPolygon", luaopen_physicPolygon },
			{ "IEPhysicNode", luaopen_physicNode },
			{ "IEThing", luaopen_thing },
			{ "IEThingCreator", luaopen_thingCreator },
			{ NULL, NULL }
		};

		for (luaL_Reg * lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
		{
			luaL_requiref(luaScript, lua_reg->name, lua_reg->func, 1);
			lua_pop(luaScript, 1);
		}

		if (luaL_dofile(luaScript, scriptName) != 0)
		{
			__IE_WARNING__("IEAttack : can not find m_luaScript file.\n");
		}

		adorningsInfo[thingID]._LuaScript = luaScript;
	}

	if (lua_getglobal(luaScript, "Create"))
	{
		lua_pushnumber(luaScript, thingID);
		lua_call(luaScript, 1, 1);

		IEThing * newThing = *((IEThing **)lua_touserdata(luaScript, -1));
		return newThing;
	}
	else
	{
		lua_settop(luaScript, 0);
	}

	return NULL;
}

IEThing * IEThingArea::FindThingByOrder(unsigned int thingOrder)
{
	for (int index = 0; index < m_visibleChunksCount; index++)
	{
		IEChunk * block = m_chunks[index]->_Chunk;

		IEContainer * childs = block->GetChilds();
		IEThing ** things = (IEThing **)(childs->GetContainer());
		unsigned int count = childs->Count();

		for (unsigned int i = 0; i < count; i++)
		{
			if (things[i]->GetOrder() == thingOrder)
			{
				return things[i];
			}
		}
	}

	return NULL;
}

IEChunk * IEThingArea::CreateChunk()
{
	return IEThingChunk::Create(m_chunkLength);
}

void IEThingArea::Visit()
{
	IEArea::Visit();

	//m_suspensionThing->Visit();
}

bool IEThingArea::AllowChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	if (tinyLocationX < 0 || tinyLocationY < 0 || tinyLocationX >= 4 || tinyLocationY >= 4)
	{
		return false;
	}
	
	for (int index = 0; index < m_thingsInfo[m_readyThingID]._OccupyCount; index++)
	{
		int location_x = locationX + (int)m_thingsInfo[m_readyThingID]._OccupyInfo[index]._X;
		int location_y = locationY + (int)m_thingsInfo[m_readyThingID]._OccupyInfo[index]._Y;

		unsigned short tinyMark = m_thingsInfo[m_readyThingID]._OccupyInfo[index]._Mask;
		unsigned short mask = 0;

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				int tinyLocation_x = tinyLocationX + x;
				int tinyLocation_y = tinyLocationY + y;

				int locationOffset_x = tinyLocation_x / 4;
				int locationOffset_y = tinyLocation_y / 4;

				tinyLocation_x = tinyLocation_x % 4;
				tinyLocation_y = tinyLocation_y % 4;

				IEThing * thing = ChooseThing(location_x + locationOffset_x, location_y + locationOffset_y, tinyLocation_x, tinyLocation_y);
				if (thing)
				{
					unsigned short zer = 1;
					zer = zer << (15 - x * 4 - y);
					mask = mask | zer;
				}
			}
		}

		if (tinyMark & mask)
		{
			return false;
		}
	}
	return true;
}

//void IEThingArea::AddThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
//{
//	IEGrid chunkLocation;
//	IEGrid explicitBlockLocation;
//
//	LocationTranslate(IEGrid(locationX, locationY), chunkLocation, explicitBlockLocation);
//	IEGrid offset = chunkLocation - m_centerChunkLocation;
//
//	if (!legalRange(offset))
//	{
//		return;
//	}
//
//	IEThingChunk * chunk = (IEThingChunk *)m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
//	chunk->AddChild(thing, explicitBlockLocation.m_x, explicitBlockLocation.m_y, tinyLocationX, tinyLocationY);
//	thing->SetTranslate(explicitBlockLocation.m_x + tinyLocationX * 0.25f, explicitBlockLocation.m_y + tinyLocationY * 0.25f);
//}
//
//void IEThingArea::HoldThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
//{
//	IEGrid chunkLocation;
//	IEGrid explicitBlockLocation;
//
//	LocationTranslate(IEGrid(locationX, locationY), chunkLocation, explicitBlockLocation);
//	IEGrid offset = chunkLocation - m_centerChunkLocation;
//
//	if (!legalRange(offset))
//	{
//		thing->SetExpress(false);
//
//		return;
//	}
//
//	IEThingChunk * chunk = (IEThingChunk *)m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
//	chunk->StanceChild(thing, explicitBlockLocation.m_x, explicitBlockLocation.m_y, tinyLocationX, tinyLocationY);
//}
//
//void IEThingArea::EraseThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
//{
//	IEGrid chunkLocation;
//	IEGrid explicitBlockLocation;
//
//	LocationTranslate(IEGrid(locationX, locationY), chunkLocation, explicitBlockLocation);
//	IEGrid offset = chunkLocation - m_centerChunkLocation;
//
//	if (!legalRange(offset))
//	{
//		return;
//	}
//
//	IEThingChunk * chunk = (IEThingChunk *)m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
//	chunk->EraseChild(explicitBlockLocation.m_x, explicitBlockLocation.m_y, tinyLocationX, tinyLocationY);
//}
//
//void IEThingArea::RemoveThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
//{
//	IEGrid chunkLocation;
//	IEGrid explicitBlockLocation;
//
//	LocationTranslate(IEGrid(locationX, locationY), chunkLocation, explicitBlockLocation);
//	IEGrid offset = chunkLocation - m_centerChunkLocation;
//
//	if (!legalRange(offset))
//	{
//		return;
//	}
//
//	IEThingChunk * chunk = (IEThingChunk *)m_chunksIndexMatrix[m_visibleRadius + offset.m_x][m_visibleRadius + offset.m_y]->_Chunk;
//	chunk->RemoveChild(explicitBlockLocation.m_x, explicitBlockLocation.m_y, tinyLocationX, tinyLocationY);
//}

IE_END