#define __IE_DLL_EXPORTS__
#include "IEGoalAwait.h"

#include "../action/IERest.h"

IE_BEGIN

IEGoalAwait::IEGoalAwait()
{
	_Mask = 0x1;
	_Opera = 0x0;
}

IEGoalAwait::~IEGoalAwait()
{

}

void IEGoalAwait::Initialization()
{

}

IEGoalAwait * IEGoalAwait::Create()
{
	IEGoalAwait * goal = new IEGoalAwait();
	goal->Initialization();
	return goal;
}

void IEGoalAwait::Begin()
{
	IERest * rest = IERest::Create();
	ChangeAction(rest);
}

void IEGoalAwait::Excute()
{

}

void IEGoalAwait::End()
{

}

IE_END