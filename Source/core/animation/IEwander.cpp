#define __IE_DLL_EXPORTS__
#include "IEwander.h"

IE_BEGIN

IEWander::IEWander(float & durationRange, IEVector & spaceRange)
{
	m_spaceRange = spaceRange;
	m_durationRange = durationRange;
}

IEWander::~IEWander()
{

}

void IEWander::Initialization()
{

}

IEWander * IEWander::Create(float durationRange, IEVector & spaceRange)
{
	IEWander * object = new IEWander(durationRange, spaceRange);
	object->Initialization();
	return object;
}

void IEWander::RandomWander()
{
	int randNumberX = rand() % 201 - 100;
	int randNumberY = rand() % 201 - 100;
	float ratioNumberX = (float)randNumberX / 100.0f;
	float ratioNumberY = (float)randNumberY / 100.0f;
	m_targetPosition = IEVector(m_spaceRange.m_x * ratioNumberX, m_spaceRange.m_y * ratioNumberY) + m_startPosition;

	int randNumber = rand() % 101;
	float ratioNumber = (float)randNumber / 100.0f;
	ratioNumber = ratioNumber > 0.2f ? ratioNumber : 0.2f;
	m_leftTime = m_durationRange * ratioNumber;
}

void IEWander::CompletedAction(IENode * node)
{
	if (!m_hasCompletedAction)
	{
		m_hasCompletedAction = true;

		const float * translate = node->GetTranslate();
		m_startPosition = IEVector(translate[0], translate[1]);;
		RandomWander();
	}
}

void IEWander::SetCircle()
{

}

void IEWander::SetLoop()
{

}

bool IEWander::Run(IENode * node)
{
	CompletedAction(node);

	const float * translate = node->GetTranslate();
	IEVector distance = m_targetPosition - IEVector(translate[0], translate[1]);;
	IEVector segment = distance / m_leftTime * IETime::Share()->GetLastFrapPassingTime();

	node->SetTranslate(translate[0] + segment.m_x, translate[1] + segment.m_y);
	m_leftTime = m_leftTime - IETime::Share()->GetLastFrapPassingTime();

	if (IsAnimationEnded())
	{
		node->SetTranslate(m_targetPosition.m_x, m_targetPosition.m_y);

		RandomWander();
		return false;
	}
	else
	{
		return false;
	}
}

IE_END