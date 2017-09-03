#define __IE_DLL_EXPORTS__
#include "IEJoint.h"

#include "../IEThingList.h"
#include "../IEthingArea.h"

#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

#define __IE_INIT_ARRAY__(__array__,__count__,__value__)\
	for (int __array__##index = 0; __array__##index < __count__; __array__##index++){\
		__array__[__array__##index]=__value__;\
	}

IEJoint::IEJoint()
{
	__IE_INIT_ARRAY__(m_round, 4, false);
	__IE_INIT_ARRAY__(m_topBorder, 4, NULL);

	m_topBackground = NULL;
}

IEJoint::~IEJoint()
{

}

void IEJoint::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEJoint * IEJoint::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEJoint * thing = new IEJoint();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEJoint::CalLasts()
{
	CheckAround();
}

void IEJoint::CheckAround()
{
	//对四周进行检测
	static IEThingArea * area = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetThing();

	IEThing * grids[4];
	grids[0] = area->GetThing(m_locations[0], m_locations[1] - 1, m_locations[2], m_locations[3]);
	grids[1] = area->GetThing(m_locations[0] + 1, m_locations[1], m_locations[2], m_locations[3]);
	grids[2] = area->GetThing(m_locations[0], m_locations[1] + 1, m_locations[2], m_locations[3]);
	grids[3] = area->GetThing(m_locations[0] - 1, m_locations[1], m_locations[2], m_locations[3]);

	for (unsigned char index = 0; index < 4; index++)
	{
		m_round[index] = false;

		if (grids[index] && grids[index]->GetThingType() == m_thingType)
		{
			m_round[index] = true;
			((IEJoint *)grids[index])->m_round[(index + 2) % 4] = true;
			((IEJoint *)grids[index])->RereadSelf();
		}
	}

	RereadSelf();
}

void IEJoint::RereadSelf()
{
	//最后当所有的都完了，那么就测算 该使用那部分的贴图 以及贴图的旋转方向了
	unsigned int aroundCount = 0;
	for (unsigned int index = 0; index < 4; index++)
	{
		if (m_round[index] == true)
		{
			aroundCount++;
		}
	}

	//考虑到方向的问题。单个thing的方向应该是可以更改的。normal不存在方向问题
	//这里是特殊thing，意味可以和旁边的同类joint或者thing连接在一起，从而改变状态
	if (aroundCount == 0)
	{
		//四面八方都没有一个thing
		ChangeGroup("body", 1);

		m_direction2 = 0;		//方向数
	}
	else if (aroundCount == 1)
	{
		//四面八方只有一个thing
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == true)
			{
				m_direction2 = index;
				break;
			}
		}

		ChangeGroup("end", 1);	//注意这里要调整方向
	}
	else if (aroundCount == 2)
	{
		//为一条横 或者为一个折角
		int direction1 = -1;
		int direction2 = -1;
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == true)
			{
				if (direction1 == -1)
				{
					direction1 = index;
				}
				else if (direction2 == -1)
				{
					direction2 = index;
				}
				else
				{
					break;
				}
			}
		}

		if (direction1 + 1 == direction2)
		{
			//说明相邻
			m_direction2 = direction1;
			ChangeGroup("corner", 1);	//注意这里要调整方向
		}
		else if (direction1 == 0 && direction2 == 3)
		{
			//也说明相邻
			m_direction2 = direction2;
			ChangeGroup("corner", 1);	//注意这里要调整方向
		}
		else
		{
			//说明为一条直线
			m_direction2 = direction1;
			ChangeGroup("line", 1);	//注意这里要调整方向
		}
	}
	else if (aroundCount == 3)
	{
		//四面八方有三个thing 找出不是thing的那一个面即可
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == false)
			{
				m_direction2 = index;
				break;
			}
		}

		m_direction2 = (m_direction2 + 2) % 4;
		ChangeGroup("fork", 1);	//注意这里要调整方向
	}
	else if (aroundCount == 4)
	{
		ChangeGroup("cross", 1);	//注意这里要调整方向

		m_direction2 = 0;
	}

	//一旦调整完毕 joint将会以正确的方式显示出来



}

void IEJoint::BuildTopSprite(unsigned int thingID)
{
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	unsigned int count = IEThingList::Share()->GetEntrysCount();

	IEString backName = IEString(entrys[thingID]._ThingName) + "_back";
	IEString borderName = IEString(entrys[thingID]._ThingName) + "_border";

	m_topBackground = IESprite::Create(backName.GetString());

	for (unsigned char index = 0; index < 4; index++)
	{
		m_topBorder[index] = IESprite::Create(borderName.GetString());
	}
}

IE_END