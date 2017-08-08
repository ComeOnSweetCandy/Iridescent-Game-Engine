#define __IE_DLL_EXPORTS__
#include "IEActionInjured.h"
#include "../IECreature.h"

IE_BEGIN

IEInjured::IEInjured()
{
	//m_actionType = __action_injured__;
	//m_actionLevel = __actionlevel_3__;
}

IEInjured::~IEInjured()
{

}

void IEInjured::Initialization()
{

}

IEInjured * IEInjured::Create()
{
	//IEInjured * action = new IEInjured();
	//action->Initialization();
	//return action;

	return NULL;
}

void IEInjured::Begin()
{
	//ChangeActionTexture("injured", 1);
	//DeleteOtherActions();

}

void IEInjured::Excute()
{
	//如果动画播放完成
	//if (1)
	//{
	//	DeleteAction(m_actionType);
	//}

}

void IEInjured::End()
{

}

IE_END