#define __IE_DLL_EXPORTS__
#include "IEActionAttack.h"

#include "../IECreature.h"
#include "../../IEprop.h"

IE_BEGIN

IEActionAttack::IEActionAttack()
{
	m_lastedTime = 0.0f;
	m_haveAttacked = false;
}

IEActionAttack::~IEActionAttack()
{

}

void IEActionAttack::Initialization()
{

}

IEActionAttack * IEActionAttack::Create()
{
	IEActionAttack * action = new IEActionAttack();
	action->Initialization();
	return action;
}

void IEActionAttack::Begin()
{
	GetCreature()->ChangeGroup("attack", 1);
}

void IEActionAttack::Excute()
{
	//要检测是否到了关键帧，到了关键帧，就可以执行操作
	if (1)
	{
		printf("attack \n");

		//产生一个触发器 damage triiger

		GetActionMachine()->ChangeAction(NULL);
	}
}

void IEActionAttack::End()
{

}

IE_END