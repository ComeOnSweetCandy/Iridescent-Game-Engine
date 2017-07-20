#define __IE_DLL_EXPORTS__
#include "IEGoalUser.h"

IE_BEGIN

IEGoalUser::IEGoalUser()
{

}

IEGoalUser::~IEGoalUser()
{

}

void IEGoalUser::Initialization()
{

}

IEGoalUser * IEGoalUser::Create()
{
	IEGoalUser * goal = new IEGoalUser();
	goal->Initialization();
	return goal;
}

void IEGoalUser::Begin()
{

}

void IEGoalUser::Excute()
{
	//never release
}

void IEGoalUser::End()
{

}

IE_END