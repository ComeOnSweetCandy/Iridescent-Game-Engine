#define __IE_DLL_EXPORTS__
#include "IEstill.h"

IE_BEGIN

IEStill::IEStill()
{

}

IEStill::~IEStill()
{

}

void IEStill::Initialization(char * still)
{
	IEAtom::SetTextureGroupName(still);
}

IEStill * IEStill::Create(char * still)
{
	IEStill * atom = new IEStill();
	atom->Initialization(still);
	return atom;
}

IE_END