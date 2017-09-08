#define __IE_DLL_EXPORTS__
#include "IEThingArea.h"

#include "IEThingCreator.h"

#include "../path/IEPathArea.h"
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

	m_entrys = IEThingList::Share()->GetEntrys();
}

IEThingArea * IEThingArea::Create(IEMap * map, int halfViewBlocks, int blockSize)
{
	IEThingArea * object = new IEThingArea();
	object->Initialization(map, halfViewBlocks, blockSize);
	return object;
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
	m_alter = new IEThingAlter();
	m_alter->_X = locationX;
	m_alter->_Y = locationY;
	m_alter->_TinyX = tinyLocationX;
	m_alter->_TinyY = tinyLocationY;
	m_alter->_ThingID = m_readyThingID;
	m_alter->_Order = m_curOrder++;
	m_alter->_ExtraOrder = 0;
	m_alter->_OperaType = __IE_THING_ALTER_OPERA_ADD__;
	m_alters->Push(m_alter);

	//创建一个新的thing
	IEThing * thing = CreateThing(m_alter->_ThingID, m_alter->_Order);
	AddThing(thing, locationX, locationY, tinyLocationX, tinyLocationY);
	thing->CheckThing(true);		//自发执行某些后续计算

	//把物理信息喂入路径网格系统
	//m_map->BuildPath(thing->GetPhysicNode());

	//放入当前场景中

	for (int index = 0; index < m_entrys[m_readyThingID]._OccupyCount; index++)
	{
		int baseLocationX = locationX + m_entrys[m_readyThingID]._OccupyInfo[index]._X;
		int baseLocationY = locationY + m_entrys[m_readyThingID]._OccupyInfo[index]._Y;
		unsigned short tinyMark = m_entrys[m_readyThingID]._OccupyInfo[index]._Mask;

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

IEThing * IEThingArea::GetThing(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	static int chunkX, chunkY, explicitX, explicitY;
	LocationTranslate(locationX, locationY, chunkX, chunkY, explicitX, explicitY);

	IEThingChunk * chunk = (IEThingChunk *)GetChunk(chunkX, chunkY);
	if (chunk)
	{
		if (IEThing * thing = chunk->GetChild(explicitX, explicitY, tinyLocationX, tinyLocationY))
		{
			int * locations = thing->GetLocations();
			if (locations[0] == locationX && locations[1] == locationY && locations[2] == tinyLocationX && locations[3] == tinyLocationY)
			{
				return thing;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

IEThing * IEThingArea::LoadChild(unsigned m_thingID, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	if (m_thingID == 0)
	{
		return NULL;
	}

	//... 这里的order的值是伪造的
	IEThing * thing = IEThing::Create(0, m_thingID, 1);
	thing->ChangeTexture((IEString(m_entrys[m_thingID]._ThingName) + "/body.png").GetString());
	m_map->BuildPath(thing->GetPhysicNode());

	AddThing(thing, locationX, locationY, tinyLocationX, tinyLocationY);
	thing->SetLocations(locationX, locationY, tinyLocationX, tinyLocationY);

	for (int index = 0; index < m_entrys[m_thingID]._OccupyCount; index++)
	{
		int baseLocationX = locationX + m_entrys[m_thingID]._OccupyInfo[index]._X;
		int baseLocationY = locationY + m_entrys[m_thingID]._OccupyInfo[index]._Y;
		unsigned short tinyMark = m_entrys[m_thingID]._OccupyInfo[index]._Mask;

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

void IEThingArea::LoadChilds(int blockX, int blockY, IEThingBlockFormat * alters)
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
			things->SetThingID(alters[index]._ThingID);
		}
	}
}

IEThing * IEThingArea::ChooseChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
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

void IEThingArea::RemoveChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	IEThing * thing = FindThingByOrder(m_choosenThingOrder);
	IEThingChunk * parent = (IEThingChunk *)(thing->GetParentNode());

	unsigned int thingID = thing->GetThingID();
	int * locations = thing->GetLocations();

	if (thing)
	{
		m_alter = new IEThingAlter();
		m_alter->_X = locations[0];
		m_alter->_Y = locations[1];
		m_alter->_TinyX = locations[2];
		m_alter->_TinyY = locations[3];
		m_alter->_ThingID = 0;
		m_alter->_ExtraOrder = thingID;
		m_alter->_OperaType = __IE_THING_ALTER_OPERA_DEL__;
		//m_alter->_ExtraOrder = thing->GetRelatedCreatedOrder();
		m_alters->Pop(m_alter);

		RemoveThing(locations[0], locations[1], locations[2], locations[3]);

		for (int index = 0; index < m_entrys[thingID]._OccupyCount; index++)
		{
			unsigned short tinyMark = m_entrys[thingID]._OccupyInfo[index]._Mask;

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
						EraseThing(locations[0] + m_entrys[m_readyThingID]._OccupyInfo[index]._X + locationOffset_x, locations[1] + m_entrys[m_readyThingID]._OccupyInfo[index]._Y + locationOffset_y, tinyLocation_x, tinyLocation_y);
					}
				}
			}
		}
	}
}

void IEThingArea::SetReadyThing(unsigned int thingID)
{
	m_readyThingID = thingID;

	if (m_readyThingID != 0)
	{
		IEPackerTexture * texture = IEPackerTexture::Create(m_entrys[thingID]._XML->FindChild("texture"));
		m_suspension->ChangeTexture(texture);
		m_suspension->ChangeGroup("default");
		m_suspension->SetDisplay(true);
	}
	else
	{
		m_suspension->SetDisplay(false);
	}
}

void IEThingArea::MouseMove(float x, float y)
{
	static int __mouseLocationX, __mouseLocationY;
	static int __mouseTinyLocationX, __mouseTinyLocationY;

	//得到鼠标当前的格子位置 以及是否开启对齐格子
	__mouseLocationX = IEMouse::Share()->_MouseLocationX;
	__mouseLocationY = IEMouse::Share()->_MouseLocationY;
	__mouseTinyLocationX = m_regularization ? 0 : IEMouse::Share()->_MouseTinyLocationX;
	__mouseTinyLocationY = m_regularization ? 0 : IEMouse::Share()->_MouseTinyLocationY;

	if (m_readyThingID)
	{
		//选择了一个 thingID 检测是否可行
		bool result = AllowChild(__mouseLocationX, __mouseLocationY, __mouseTinyLocationX, __mouseTinyLocationY);

		if (result)
		{
			m_suspension->SetBackColor(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			m_suspension->SetBackColor(1.0f, 0.0f, 0.0f, 0.7f);
		}
		m_suspension->SetBackColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_suspension->SetTranslate(__mouseLocationX + __mouseTinyLocationX * 0.25f, __mouseLocationY + __mouseTinyLocationY * 0.25f);
		m_suspension->Visit();
	}
	else
	{
		//没有选择 thingID 亮起待选择
		IEThing * thing = ChooseChild(__mouseLocationX, __mouseLocationY, __mouseTinyLocationX, __mouseTinyLocationY);
	}
}

void IEThingArea::MouseCancel()
{
	m_readyThingID = 0;
	m_choosenThingOrder = 0;

	m_suspension->SetDisplay(false);
}

void IEThingArea::MouseClick()
{
	if (m_readyThingID)
	{
		if (m_regularization)
		{
			AddChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY, 0, 0);
		}
		else
		{
			AddChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY, IEMouse::Share()->_MouseTinyLocationX, IEMouse::Share()->_MouseTinyLocationY);
		}
	}
	else
	{
		IEThing * thing = ChooseChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY, IEMouse::Share()->_MouseTinyLocationX, IEMouse::Share()->_MouseTinyLocationY);
		m_choosenThingOrder = thing->GetOrder();
	}
}

void IEThingArea::MouseBrush()
{
	if (m_readyThingID)
	{
		AddChild(IEMouse::Share()->_MouseLocationX, IEMouse::Share()->_MouseLocationY, IEMouse::Share()->_MouseTinyLocationX, IEMouse::Share()->_MouseTinyLocationY);
	}
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

void IEThingArea::LoadChunk(int blockX, int blockY)
{
	m_map->LoadThingChunk(blockX, blockY);
}

IEChunk * IEThingArea::CreateChunk()
{
	return IEThingChunk::Create(m_chunkLength);
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

bool IEThingArea::AllowChild(int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	if (tinyLocationX < 0 || tinyLocationY < 0 || tinyLocationX >= 4 || tinyLocationY >= 4)
	{
		return false;
	}
	
	for (int index = 0; index < m_entrys[m_readyThingID]._OccupyCount; index++)
	{
		int location_x = locationX + (int)m_entrys[m_readyThingID]._OccupyInfo[index]._X;
		int location_y = locationY + (int)m_entrys[m_readyThingID]._OccupyInfo[index]._Y;

		unsigned short tinyMark = m_entrys[m_readyThingID]._OccupyInfo[index]._Mask;
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

				IEThing * thing = ChooseChild(location_x + locationOffset_x, location_y + locationOffset_y, tinyLocation_x, tinyLocation_y);
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

void IEThingArea::AddThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	static int chunkX, chunkY, explicitX, explicitY;
	LocationTranslate(locationX, locationY, chunkX, chunkY, explicitX, explicitY);

	IEThingChunk * chunk = (IEThingChunk *)GetChunk(chunkX, chunkY);
	if (chunk)
	{
		chunk->AddChild(thing, explicitX, explicitY, tinyLocationX, tinyLocationY);
		thing->SetLocations(locationX, locationY, tinyLocationX, tinyLocationY);
		thing->SetTranslate(explicitX + tinyLocationX * 0.25f, explicitY + tinyLocationY * 0.25f);
	}
	else
	{
#ifdef __IE_DEBUG__
		__IE_ERROR__("IEThingArea : Function AddThing : error.\n");
#endif
	}
}

void IEThingArea::HoldThing(IEThing * thing, int locationX, int locationY, unsigned char tinyLocationX, unsigned char tinyLocationY)
{
	static int chunkX, chunkY, explicitX, explicitY;
	LocationTranslate(locationX, locationY, chunkX, chunkY, explicitX, explicitY);

	IEThingChunk * chunk = (IEThingChunk *)GetChunk(chunkX, chunkY);
	if (chunk)
	{
		chunk->StanceChild(thing, explicitX, explicitY, tinyLocationX, tinyLocationY);
	}
	else
	{
		//本来应该占据其它的格子位置，但是因为在边缘位置，其它的chunk未正常显示，即跨区域的thing
		thing->SetExpress(false);
	}
}

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