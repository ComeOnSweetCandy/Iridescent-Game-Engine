#define __IE_DLL_EXPORTS__
#include "IEDoorInducation.h"

#include "../IEthingArea.h"
#include "../../../trigger/IETriggerWarn.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEDoorInducation::IEDoorInducation()
{
	m_lastSwitch = false;
	m_switch = false;
}

IEDoorInducation::~IEDoorInducation()
{

}

void IEDoorInducation::Initialization(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEThing::Initialization(thingType, thingID, thingOrder);
}

IEDoorInducation * IEDoorInducation::Create(unsigned int thingType, unsigned int thingID, unsigned int thingOrder)
{
	IEDoorInducation * thing = new IEDoorInducation();
	thing->Initialization(thingType, thingID, thingOrder);
	return thing;
}

void IEDoorInducation::Live()
{
	if (m_switch != m_lastSwitch)
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
	m_lastSwitch = m_switch;
	m_switch = false;
}

void IEDoorInducation::CheckThing(bool active)
{
	IEThingLine::CheckThing(active);

	if (active)
	{
		BindSelfTrigger();
	}
}

void IEDoorInducation::TriggerStrike(IEPhysicNode * physicNode)
{
	//˵���������� ���ʱ��ת��״̬
	m_switch = true;
}

void IEDoorInducation::BindSelfTrigger()
{
	//��ȡ��������Ϣ
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * physicXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");

	m_triggers = IETriggerWarn::Create(physicXML, true, true);														//����һ��������Ч��warn������
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEDoorInducation::TriggerStrike));							//�������
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);	//�趨λ��
}

IE_END