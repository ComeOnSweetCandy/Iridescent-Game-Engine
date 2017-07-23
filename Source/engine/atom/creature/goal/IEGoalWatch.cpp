#define __IE_DLL_EXPORTS__
#include "IEGoalWatch.h"

#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEGoalWatch::IEGoalWatch()
{
	_Mask = 0x2;
	_Opera = 0x0;

	m_cycle = 10;
}

IEGoalWatch::~IEGoalWatch()
{

}

void IEGoalWatch::Initialization()
{

}

IEGoalWatch * IEGoalWatch::Create()
{
	IEGoalWatch * goal = new IEGoalWatch();
	goal->Initialization();
	return goal;
}

void IEGoalWatch::Begin()
{

}

void IEGoalWatch::Excute()
{
	static unsigned char _curCircle = 0;
	_curCircle++;
	if (_curCircle >= m_cycle)
	{
		//置零
		_curCircle = 0;

		//获取当前场面上所有的creature
		IEContainer * creatures = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();

		//监视的目标为



	}
}

void IEGoalWatch::End()
{

}

IE_END