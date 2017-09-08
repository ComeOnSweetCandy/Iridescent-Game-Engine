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
		//跟上一次状态不一样 那么
		if (m_switch == true)
		{
			ChangeState("open");
		}
		else if (m_switch == false)
		{
			ChangeState("close");
		}
	}

	//这里应该设定一个 执行一次动画后 回调一个函数
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
	//说明被触发了 这个时候转换状态
	m_switch = true;
}

void IEDoorInducation::BindSelfTrigger()
{
	//读取触发器信息
	IEThingEntry * entrys = IEThingList::Share()->GetEntrys();
	IEXml * _xml = entrys[m_thingID]._XML;
	IEXml * physicXML = _xml->FindChild("property")->FindChild("trigger")->FindChild("physic");

	m_triggers = IETriggerWarn::Create(physicXML, true, true);														//建立一个永久有效的warn触发器
	m_triggers->ActivateTrigger(this, IETrggerStrike(&IEDoorInducation::TriggerStrike));							//激活触发器
	m_triggers->SetPhysicPosition(m_physicNode->GetPhysicPosition().m_x, m_physicNode->GetPhysicPosition().m_y);	//设定位置
}

IE_END