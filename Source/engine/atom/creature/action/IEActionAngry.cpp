#define __IE_DLL_EXPORTS__
#include "IEActionAngry.h"

#include "../IECreature.h"

IE_BEGIN

IEActionAngry::IEActionAngry()
{

}

IEActionAngry::~IEActionAngry()
{

}

void IEActionAngry::Initialization()
{

}

IEActionAngry * IEActionAngry::Create()
{
	IEActionAngry * state = new IEActionAngry();
	state->Initialization();
	return state;
}

void IEActionAngry::Begin()
{
	GetCreature()->ChangeGroup("angry");
}

void IEActionAngry::Excute()
{

}

void IEActionAngry::End()
{

}

IE_END