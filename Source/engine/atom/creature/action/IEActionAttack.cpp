#define __IE_DLL_EXPORTS__
#include "IEActionAttack.h"

#include "../IECreature.h"
#include "../../prop/IEProp.h"

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
<<<<<<< HEAD

	//���Ȼ�ȡ��ʲô����

	//�ı䶯��
	GetCreature()->ChangeGroup("attack", __creature_part_body__);
	//GetCreature()->ChangeGroup("attack", 1, 1, IEActionAttack::ActionEnd);

	//��Ҫһ���������� ����������

	//����һ��������

=======
	GetCreature()->ChangeGroup("attack", __creature_part_body__, 1, this, (IEFunctionTexturePlayFinished)(&IEActionAttack::ActionEnd));
>>>>>>> 1d3f5ff8135e4975ad14428686823af32cca44ed
}

void IEActionAttack::Excute()
{
	//Ҫ����Ƿ��˹ؼ�֡�����˹ؼ�֡���Ϳ���ִ�в���
	//if (1)
	//{
	//	//����һ�������� damage triiger

	//	GetActionMachine()->ChangeAction(NULL);
	//}
}

void IEActionAttack::End()
{

}

void IEActionAttack::ActionEnd()
{
	GetCreature()->ChangeGroup("rest", __creature_part_body__);
	GetActionMachine()->ChangeAction(NULL);
}

IE_END