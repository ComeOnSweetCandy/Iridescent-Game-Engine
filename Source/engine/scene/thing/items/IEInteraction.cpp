#define __IE_DLL_EXPORTS__
#include "IEInteraction.h"

#include "../IEthingArea.h"
#include "../../../trigger/IEinteractionTrigger.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEInteraction::IEInteraction()
{
	m_switch = false;
}

IEInteraction::~IEInteraction()
{

}

void IEInteraction::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEInteraction * IEInteraction::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEInteraction * thing = new IEInteraction();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEInteraction::CheckAround(bool active)
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

void IEInteraction::Live()
{
	//do something
}

void IEInteraction::TriggerStrike(IEPhysicNode * physicNode)
{
	//˵���������� ���ʱ��ת��״̬
	m_switch = !m_switch;

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

void IEInteraction::BindTriggers()
{
	//��ȡ��������Ϣ
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * physicXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");

	m_triggers = IEInteractionTrigger::Create(physicXML, true, true);												//����һ��������Ч��warn������
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEInteraction::TriggerStrike));								//�������
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);	//�趨λ��
}

void IEInteraction::RereadSelf()
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