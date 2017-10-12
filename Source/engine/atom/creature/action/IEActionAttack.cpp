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

	//首先获取是什么动作

	//改变动作
	GetCreature()->ChangeGroup("attack", __creature_part_body__);
	//GetCreature()->ChangeGroup("attack", 1, 1, IEActionAttack::ActionEnd);

	//需要一个反馈函数 来处理问题

	//产生一个触发器

=======
	GetCreature()->ChangeGroup("attack", __creature_part_body__, 1, this, (IEFunctionTexturePlayFinished)(&IEActionAttack::ActionEnd));
>>>>>>> 1d3f5ff8135e4975ad14428686823af32cca44ed
}

void IEActionAttack::Excute()
{
	//要检测是否到了关键帧，到了关键帧，就可以执行操作
	//if (1)
	//{
	//	//产生一个触发器 damage triiger

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