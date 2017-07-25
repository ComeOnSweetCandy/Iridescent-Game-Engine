#define __IE_DLL_EXPORTS__
#include "IEActionRest.h"

#include "../IECreature.h"

IE_BEGIN

IERest::IERest()
{
	m_waitTime = 0.0f;
}

IERest::~IERest()
{

}

void IERest::Initialization()
{

}

IERest * IERest::Create()
{
	IERest * state = new IERest();
	state->Initialization();
	return state;
}

void IERest::Begin()
{
	GetCreature()->ChangeGroup("rest");
}

void IERest::Excute()
{

}

void IERest::End()
{

}

IE_END