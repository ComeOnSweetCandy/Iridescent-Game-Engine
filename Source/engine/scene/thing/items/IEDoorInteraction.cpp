#define __IE_DLL_EXPORTS__
#include "IEDoorInteraction.h"

#include "../IEthingArea.h"
#include "../../../trigger/IETriggerInteraction.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEDoorInteraction::IEDoorInteraction()
{
	m_switch = false;
}

IEDoorInteraction::~IEDoorInteraction()
{

}

void IEDoorInteraction::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEDoorInteraction * IEDoorInteraction::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEDoorInteraction * thing = new IEDoorInteraction();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEDoorInteraction::CheckThing(bool active)
{
	IEThingLine::CheckThing(active);

	if (active)
	{
		BindTriggers();
	}
}

void IEDoorInteraction::Live()
{
	//do something
}

void IEDoorInteraction::TriggerStrike(IEPhysicNode * physicNode)
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

void IEDoorInteraction::BindTriggers()
{
	//��ȡ��������Ϣ
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * triggerXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");
	int triggerType = _xml->FindChild("property")->FindChild("trigger")->FindChild("triggetType")->ValueInt();

	m_triggers = IETriggerInteraction::Create(triggerXML, true, true);													//����һ��������Ч��warn������
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEDoorInteraction::TriggerStrike));								//�������
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);		//�趨λ��
}

IE_END