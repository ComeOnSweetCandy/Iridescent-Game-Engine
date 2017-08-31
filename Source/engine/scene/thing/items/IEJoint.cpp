#define __IE_DLL_EXPORTS__
#include "IEJoint.h"

#include "../IEThingList.h"

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

void IEJoint::Initialization(unsigned int thingID)
{
	IEThing::Initialization(thingID);
}

IEJoint * IEJoint::Create(unsigned int thingID)
{
	return NULL;
}

void IEJoint::SetRound(unsigned char roundIndex, unsigned int thingID)
{
	if (m_thingID == thingID)
	{
		//如果两者的thingID相同 才会继续下一步的步骤
		unsigned char index = (roundIndex + 2) % 4;

		m_round[index] = true;
	}
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
		ChangeGroup("normal", 1);
	}
	else if (aroundCount == 1)
	{
		//四面八方只有一个thing
		int direction = 0;
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == true)
			{
				direction = index;
				break;
			}
		}

		ChangeGroup("end", 1);	//注意这里要调整方向
	}
	else if (aroundCount == 2)
	{
		//为一条横 或者为一个折角
		int direction;
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
			direction = direction1;
			ChangeGroup("corner", 1);	//注意这里要调整方向
		}
		else if (direction1 == 0 && direction2 == 3)
		{
			//也说明相邻
			direction = direction2;
			ChangeGroup("corner", 1);	//注意这里要调整方向
		}
		else
		{
			//说明为一条直线
			direction = direction1;
			ChangeGroup("line", 1);	//注意这里要调整方向
		}
	}
	else if (aroundCount == 3)
	{
		//四面八方有三个thing 找出不是thing的那一个面即可
		int direction = 0;
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == false)
			{
				direction = index;
				break;
			}
		}

		direction = (direction + 2) % 4;
		ChangeGroup("fork", 1);	//注意这里要调整方向
	}
	else if (aroundCount == 4)
	{
		ChangeGroup("cross", 1);	//注意这里要调整方向
	}

	m_direction;

	//一旦调整完毕 joint将会以正确的方式显示出来
	


}

void IEJoint::BuildTopSprite(unsigned int thingID)
{
	IEThingEntry * infos = IEAdorningsInfoManager::Share()->GetAdorningsInfoList();
	unsigned int count = IEAdorningsInfoManager::Share()->GetAdorningsInfoCount();

	IEString backName = IEString(infos[thingID]._ThingName) + "_back";
	IEString borderName = IEString(infos[thingID]._ThingName) + "_border";

	m_topBackground = IESprite::Create(backName.GetString());

	for (unsigned char index = 0; index < 4; index++)
	{
		m_topBorder[index] = IESprite::Create(borderName.GetString());
	}
	
	

}

IE_END