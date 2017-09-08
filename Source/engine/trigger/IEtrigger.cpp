#define __IE_DLL_EXPORTS__
#include "IEtrigger.h"

#include "../atom/IEatom.h"
#include "../../core/container/IEcontianer.h"
#include "../../interface/cmd/IEapplication.h"

IE_BEGIN

IETrigger::IETrigger()
{
	m_triggerType = __trigger_type_count__;

	m_allowStrikeRepeat = false;
	m_allowStrikeRepeatByOne = false;

	m_strikeNodes = IEContainer::CreateAndRetain();
}

IETrigger::~IETrigger()
{
	if (m_strikeNodes)
	{
		m_strikeNodes->Release();
		m_strikeNodes = NULL;
	}

	//������������������ڵ�����
	//IEApplication::Share()->GetCurrentActiveScene()->GetTriggerManager()->DelTrigger(this);
}

void IETrigger::Initialization(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IEPhysicNode::Initialization(physicXML);
	
	IETrigger::SetAllowStrikeRepeat(allowStrikeRepeat);
	IETrigger::SetAllowStrikeRepeatByOne(allowStrikeRepeatByOne);

	//��������ӽ���������������
	//IEApplication::Share()->GetCurrentActiveScene()->GetTriggerManager()->AddTrigger(this);
}

IETrigger * IETrigger::Create(IEXml * physicXML, bool allowStrikeRepeat, bool allowStrikeRepeatByOne)
{
	IETrigger * trigger = new IETrigger();
	trigger->Initialization(physicXML, allowStrikeRepeat, allowStrikeRepeatByOne);
	return trigger;
}

IETriggerType IETrigger::GetTriggerType()
{
	return m_triggerType;
}

void IETrigger::SetAllowStrikeRepeat(bool allowStrikeRepeat)
{
	m_allowStrikeRepeat = allowStrikeRepeat;
}

void IETrigger::SetAllowStrikeRepeatByOne(bool allowStrikeRepeatByOne)
{
	m_allowStrikeRepeatByOne = allowStrikeRepeatByOne;
}

void IETrigger::ActivateTrigger(IEAtom * self, IETrggerStrike function)
{
	//�󶨻ص�
	m_attachAtom = self;
	m_function = function;

	//������������
	BindToWorld();
}

void IETrigger::RunTrigger()
{
	//do something here
}

void IETrigger::Collision(IEPhysicNode * physicNode)
{
	//���ȼ���Ƿ�Ӧ������
	if (m_allowStrikeRepeat)
	{
		TriggerStrike(physicNode);
	}
	else
	{
		//�ж��Ƿ��Ѿ�����
		static bool hasStriked = false;
		if (hasStriked == false)
		{
			//ֻ����һ��
			hasStriked = true;
			TriggerStrike(physicNode);
		}
	}
}

void IETrigger::TriggerStrike(IEPhysicNode * physicNode)
{
	(m_attachAtom->*m_function)(physicNode);
}

IE_END