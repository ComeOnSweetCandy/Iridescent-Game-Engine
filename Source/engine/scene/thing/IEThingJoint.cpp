#define __IE_DLL_EXPORTS__
#include "IEThingJoint.h"

#include "IEThingList.h"
#include "IEthingArea.h"

#include "../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEThingJoint::IEThingJoint()
{
	__IE_INIT_ARRAY__(m_round, 4, false);
}

IEThingJoint::~IEThingJoint()
{

}

void IEThingJoint::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEThingJoint * IEThingJoint::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThingJoint * thing = new IEThingJoint();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEThingJoint::CheckThing(bool active)
{
	//对四周八个方向进行检测
	//这个情况下暂时只需要检测四周
	static IEThingArea * area = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetThing();

	IEThing * grids[8];
	grids[0] = area->GetThing(m_locations[0], m_locations[1] - 1, m_locations[2], m_locations[3]);
	grids[2] = area->GetThing(m_locations[0] + 1, m_locations[1], m_locations[2], m_locations[3]);
	grids[4] = area->GetThing(m_locations[0], m_locations[1] + 1, m_locations[2], m_locations[3]);
	grids[6] = area->GetThing(m_locations[0] - 1, m_locations[1], m_locations[2], m_locations[3]);

	for (unsigned char index = 0; index < 8; index = index + 2)
	{
		m_round[index] = false;

		if (grids[index] && grids[index]->GetThingType() == m_thingType)
		{
			m_round[index] = true;

			if (active)
			{
				((IEThingJoint *)grids[index])->m_round[(index + 4) % 8] = true;
				grids[index]->CheckThing(false);
			}
			else
			{
				//do nothing
			}
		}
	}

	RereadSelf();
}

void IEThingJoint::RereadSelf()
{
	//最后当所有的都完了，那么就测算 该使用那部分的贴图 以及贴图的旋转方向了
	unsigned int aroundCount = 0;
	for (unsigned int index = 0; index < 8; index = index + 2)
	{
		if (m_round[index] == true)
		{
			aroundCount++;
		}
	}

	//考虑到方向的问题。单个thing的方向应该是可以更改的。normal不存在方向问题
	//这里是特殊thing，意味可以和旁边的同类joint或者thing连接在一起，从而改变状态
	char finalGroupName[256];

	if (aroundCount == 0)
	{
		sprintf(finalGroupName, "body");
	}
	else if (aroundCount == 1)
	{
		//四面八方只有一个thing
		for (unsigned int index = 0; index < 8; index = index + 2)
		{
			if (m_round[index] == true)
			{
				m_direction = index;
				break;
			}
		}

		sprintf(finalGroupName, "end_%d", m_direction);
	}
	else if (aroundCount == 2)
	{
		//为一条横 或者为一个折角
		int direction1 = -1;
		int direction2 = -1;
		for (unsigned int index = 0; index < 8; index = index + 2)
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
			m_direction = direction1;
			sprintf(finalGroupName, "corner_%d", m_direction);
		}
		else if (direction1 == 0 && direction2 == 3)
		{
			//也说明相邻
			m_direction = direction2;
			sprintf(finalGroupName, "corner_%d", m_direction);
		}
		else
		{
			//说明为一条直线
			m_direction = (direction1 + 2) % 8;
			sprintf(finalGroupName, "line_%d", m_direction);
		}
	}
	else if (aroundCount == 3)
	{
		//四面八方有三个thing 找出不是thing的那一个面即可
		for (unsigned int index = 0; index < 8; index = index + 2)
		{
			if (m_round[index] == false)
			{
				m_direction = index;
				break;
			}
		}

		m_direction = (m_direction + 4) % 8;
		sprintf(finalGroupName, "fork_%d", m_direction);
	}
	else if (aroundCount == 4)
	{
		m_direction = 0;
		sprintf(finalGroupName, "cross");
	}

	//一旦调整完毕 joint将会以正确的方式显示出来
	ChangeGroup(finalGroupName, 1);
}

IE_END