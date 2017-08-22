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
	//Ҫ����Ƿ��˹ؼ�֡�����˹ؼ�֡���Ϳ���ִ�в���
	if (1)
	{
		printf("attack \n");

		//����һ�������� damage triiger

		GetActionMachine()->ChangeAction(NULL);
	}
}

void IEActionAttack::End()
{

}

IE_END