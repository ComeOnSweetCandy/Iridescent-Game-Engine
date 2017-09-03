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
	//�����ܽ��м��
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
	//������еĶ����ˣ���ô�Ͳ��� ��ʹ���ǲ��ֵ���ͼ �Լ���ͼ����ת������
	unsigned int aroundCount = 0;
	for (unsigned int index = 0; index < 4; index++)
	{
		if (m_round[index] == true)
		{
			aroundCount++;
		}
	}

	//���ǵ���������⡣����thing�ķ���Ӧ���ǿ��Ը��ĵġ�normal�����ڷ�������
	//����������thing����ζ���Ժ��Աߵ�ͬ��joint����thing������һ�𣬴Ӷ��ı�״̬
	if (aroundCount == 0)
	{
		//����˷���û��һ��thing
		ChangeGroup("body", 1);

		m_direction2 = 0;		//������
	}
	else if (aroundCount == 1)
	{
		//����˷�ֻ��һ��thing
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == true)
			{
				m_direction2 = index;
				break;
			}
		}

		ChangeGroup("end", 1);	//ע������Ҫ��������
	}
	else if (aroundCount == 2)
	{
		//Ϊһ���� ����Ϊһ���۽�
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
			//˵������
			m_direction2 = direction1;
			ChangeGroup("corner", 1);	//ע������Ҫ��������
		}
		else if (direction1 == 0 && direction2 == 3)
		{
			//Ҳ˵������
			m_direction2 = direction2;
			ChangeGroup("corner", 1);	//ע������Ҫ��������
		}
		else
		{
			//˵��Ϊһ��ֱ��
			m_direction2 = direction1;
			ChangeGroup("line", 1);	//ע������Ҫ��������
		}
	}
	else if (aroundCount == 3)
	{
		//����˷�������thing �ҳ�����thing����һ���漴��
		for (unsigned int index = 0; index < 4; index++)
		{
			if (m_round[index] == false)
			{
				m_direction2 = index;
				break;
			}
		}

		m_direction2 = (m_direction2 + 2) % 4;
		ChangeGroup("fork", 1);	//ע������Ҫ��������
	}
	else if (aroundCount == 4)
	{
		ChangeGroup("cross", 1);	//ע������Ҫ��������

		m_direction2 = 0;
	}

	//һ��������� joint��������ȷ�ķ�ʽ��ʾ����



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