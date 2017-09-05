#define __IE_DLL_EXPORTS__
#include "IEInductionDoor.h"

#include "../IEthingArea.h"

#include "../../../../interface/cmd/IEapplication.h"

#include "../../../../physic/physicEdge/IEphysicCircle.h"
#include "../../../trigger/IEWarnTrigger.h"

IE_BEGIN

IEInductionDoor::IEInductionDoor()
{
	m_switch = false;
}

IEInductionDoor::~IEInductionDoor()
{

}

void IEInductionDoor::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEInductionDoor * IEInductionDoor::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEInductionDoor * thing = new IEInductionDoor();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEInductionDoor::Live()
{
	static bool lastSwitch = false;

	if (m_switch != lastSwitch)
	{
		//����һ��״̬��һ�� ��ô
		if (m_switch == true)
		{
			ChangeState("open");
		}
		else if (m_switch == false)
		{
			ChangeState("close");
		}
	}

	//����Ӧ���趨һ�� ִ��һ�ζ����� �ص�һ������

	lastSwitch = m_switch;
	m_switch = false;
}

void IEInductionDoor::CheckAround(bool active)
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

		if (grids[index] && grids[index]->GetThingType() == 1)
		{
			m_round[index] = true;
		}
	}

	BindTriggers();
	RereadSelf();
}

void IEInductionDoor::TriggerStrike(IEPhysicNode * physicNode)
{
	//˵���������� ���ʱ��ת��״̬
	m_switch = true;
}

void IEInductionDoor::BindTriggers()
{
	//�趨������
	IEPhysicCircleInfo * in = new IEPhysicCircleInfo();
	in->m_physicEdgeType = __edge_circle__;
	in->m_radius = 2.0f;
	in->m_vertexsCount = 16;

	IEPhysicCircle * edge = IEPhysicCircle::Create(in);
	m_triggers = IEWarnTrigger::Create(edge, __physic_air_node__, true, true);				//����һ��������Ч��warn������
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEInductionDoor::TriggerStrike));		//�������
}

void IEInductionDoor::RereadSelf()
{
	//����Ա� Ϊtrue
	//���뿼���ŵķ��� ֻ��hr vr���ַ���
	char finalGroupName[256];

	if (m_round[0] == true && m_round[2] == true && m_round[1] == false && m_round[3] == false)
	{
		sprintf(finalGroupName, "line_%d", 1);
	}
	else if (m_round[0] == false && m_round[2] == false && m_round[1] == true && m_round[3] == true)
	{
		sprintf(finalGroupName, "line_%d", 0);
	}
	else
	{
		sprintf(finalGroupName, "line_%d", 0);
		__IE_EDIT_DIALOG__("you can't add a door to such a place.\n");
	}

	ChangeState("close");
	ChangeGroup(finalGroupName, 1);
}

IE_END