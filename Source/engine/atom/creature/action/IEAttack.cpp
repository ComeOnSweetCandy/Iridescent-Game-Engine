#define __IE_DLL_EXPORTS__
#include "IEattack.h"
#include "../IECreature.h"
#include "../../IEprop.h"

IE_BEGIN

IEAttack::IEAttack()
{
	m_actionType = __action_attack__;
	m_actionLevel = __actionlevel_2__;

	m_lastedTime = 0.0f;
	m_haveAttacked = false;
}

IEAttack::~IEAttack()
{

}

void IEAttack::Initialization()
{

}

IEAttack * IEAttack::Create()
{
	IEAttack * action = new IEAttack();
	action->Initialization();
	return action;
}

bool IEAttack::Begin()
{
	ChangeActionTexture("attack", 1);
	DeleteOtherActions();
	return true;
}

void IEAttack::Attack()
{

}

bool IEAttack::Excute()
{
	m_lastedTime = m_lastedTime + IETime::Share()->GetLastFrapPassingTime();
	IECreature * m_creature = GetActionCreature();

	if (!m_haveAttacked && m_creature->IsTriggerFrap())
	{
		m_haveAttacked = true;
		Attack();
	}

	return true;
}

bool IEAttack::End()
{
	return true;
}

IE_END