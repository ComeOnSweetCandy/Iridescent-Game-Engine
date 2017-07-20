#define __IE_DLL_EXPORTS__
#include "IEinjured.h"
#include "../IECreature.h"

IE_BEGIN

IEInjured::IEInjured()
{
	m_actionType = __action_injured__;
	m_actionLevel = __actionlevel_3__;
}

IEInjured::~IEInjured()
{

}

void IEInjured::Initialization()
{

}

IEInjured * IEInjured::Create()
{
	IEInjured * action = new IEInjured();
	action->Initialization();
	return action;
}

bool IEInjured::Begin()
{
	ChangeActionTexture("injured", 1);
	DeleteOtherActions();

	return true;
}

bool IEInjured::Excute()
{
	//如果动画播放完成
	//if (1)
	//{
	//	DeleteAction(m_actionType);
	//}

	return true;
}

bool IEInjured::End()
{
	return true;
}

IE_END