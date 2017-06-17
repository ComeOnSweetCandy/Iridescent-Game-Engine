#define __IE_DLL_EXPORTS__
#include "IEvertigo.h"

IE_BEGIN

IEVertigo::IEVertigo()
{
	m_actionType = __action_vertigo__;
	m_leftTime = 10.0f;
}

IEVertigo::~IEVertigo()
{

}

void IEVertigo::Initialization()
{

}

IEVertigo * IEVertigo::Create()
{
	IEVertigo * state = new IEVertigo();
	state->Initialization();
	return state;
}

bool IEVertigo::Begin()
{
	ChangeActionTexture("vertigo");
	DeleteOtherActions();
	return true;
}

bool IEVertigo::Excute()
{
	m_leftTime -= 0.01f;
	printf("vertigo left time: %f\n", m_leftTime);
	if (m_leftTime <= 0.0f)
	{
		ChangeAction(__action_await__);
	}
	return true;
}

bool IEVertigo::End()
{
	return true;
}

IE_END