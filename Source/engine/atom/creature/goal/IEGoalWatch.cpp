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
		//����
		_curCircle = 0;

		//��ȡ��ǰ���������е�creature
		IEContainer * creatures = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();

		//���ӵ�Ŀ��Ϊ



	}
}

void IEGoalWatch::End()
{

}

IE_END