#define __IE_DLL_EXPORTS__
#include "IEGoalWatch.h"

#include "IEGoalGo.h"
#include "../IECreature.h"
#include "../../../../interface/cmd/IEapplication.h"

IE_BEGIN

IEGoalWatch::IEGoalWatch()
{
	_Mask = 0x2;
	_Opera = 0x0;

	m_cycle = 20;
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
	GetCreature()->Rest();
}

void IEGoalWatch::Excute()
{
	static unsigned char _curCircle = 0;
	_curCircle++;

	if (_curCircle >= m_cycle)
	{
		//置零
		_curCircle = 0;

		//得到自身的creature
		IECreature * self = GetCreature();

		//获取当前场面上所有的creature
		IEContainer * container = IEApplication::Share()->GetCurrentActiveScene()->GetCreatures();
		IECreature ** creatures = (IECreature **)(container->GetContainer());
		unsigned int count = container->Count();

		//监视的目标为
		for (unsigned int index = 0; index < count; index++)
		{
			bool res = __CreatureOpposite(self, creatures[index]);
			if (res)
			{
				//两者对立
				float * aPosition = self->GetTranslate();
				float * bPosition = creatures[index]->GetTranslate();

				//检测是否在范围内
				float length = IEVector(aPosition[0] - bPosition[0], aPosition[1] - bPosition[1]).Length();
				if (length <= self->GetCreatureInfo()->_View)
				{
					if (m_watchSomething == false)
					{
						m_watchSomething = true;
						self->Warning(creatures[index]);
					}

					return;
				}
			}
		}

		if (m_watchSomething == true)
		{
			m_watchSomething = false;

			self->Rest();
		}
	}
}

void IEGoalWatch::End()
{

}

IE_END