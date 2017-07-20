#define __IE_DLL_EXPORTS__
#include "IEcast.h"

#include "../IECreature.h"
#include "../../IEprop.h"

IE_BEGIN

IECast::IECast()
{
	m_actionType = __action_cast__;
	m_actionLevel = __actionlevel_2__;

	m_skillID = 0;
	m_lastedTime = 0.0f;
	m_haveCasted = false;
}

IECast::~IECast()
{

}

void IECast::Initialization(unsigned int skillID)
{

}

IECast * IECast::Create(unsigned int skillID)
{
	IECast * action = new IECast();
	action->Initialization(skillID);
	return action;
}

bool IECast::Begin()
{
	ChangeActionTexture("attack", 1);
	DeleteOtherActions();
	return true;
}

void IECast::Cast()
{

}

bool IECast::Excute()
{
	m_lastedTime = m_lastedTime + IETime::Share()->GetLastFrapPassingTime();
	IECreature * m_creature = GetActionCreature();

	if (!m_haveCasted && m_creature->IsTriggerFrap())
	{
		m_haveCasted = true;
		Cast();
	}

	return true;
}

bool IECast::End()
{
	return true;
}

IE_END