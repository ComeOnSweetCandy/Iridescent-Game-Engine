#define __IE_DLL_EXPORTS__
#include "IEuseProp.h"
#include "../atom/creature/IEplayer.h"

IE_BEGIN

IEUseProp::IEUseProp()
{
	m_actionType = __action_useProp__;
	m_actionLevel = __actionlevel_2__;

	m_lastedTime = 0.0f;
	m_haveUsed = false;
}

IEUseProp::~IEUseProp()
{

}

void IEUseProp::Initialization(int packIndex)
{
	m_packIndex = packIndex;
}

IEUseProp * IEUseProp::Create()
{
	IEUseProp * action = new IEUseProp();
	action->Initialization(1);
	return action;
}

IEUseProp * IEUseProp::Create(int packIndex)
{
	IEUseProp * action = new IEUseProp();
	action->Initialization(packIndex);
	return action;
}

bool IEUseProp::Begin()
{
	IEPlayer * player = (IEPlayer *)GetActionNode();
	IEPropPack * pack = player->GetPlayersPack();
	bool have = pack->HaveProp(m_packIndex);

	if (have)
	{
		ChangeActionTexture("attack", 1);
		DeleteOtherActions();
		return true;
	}
	else
	{
		DeleteAction(__action_useProp__);
		return false;
	}
}

bool IEUseProp::Excute()
{
	m_lastedTime = m_lastedTime + IETime::Share()->GetLastFrapPassingTime();
	IECreature * m_creature = GetActionCreature();

	if (!m_haveUsed && m_creature->IsTriggerFrap())
	{
		m_haveUsed = true;
		UseProp();
	}

	return true;
}

void IEUseProp::UseProp()
{
	IEPlayer * player = (IEPlayer *)GetActionNode();
	IEPropPack * pack = player->GetPlayersPack();
	pack->UseProp(m_packIndex);
}

bool IEUseProp::End()
{
	return true;
}

IE_END