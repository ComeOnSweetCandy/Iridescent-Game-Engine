#define __IE_DLL_EXPORTS__
#include "IEparticle.h"

IE_BEGIN

IEParticle::IEParticle()
{

}

IEParticle::~IEParticle()
{

}

void IEParticle::Initialization(char * textureName)
{
	IESprite::Initialization(textureName);
}

IEParticle * IEParticle::Create(char * textureName)
{
	IEParticle * particle = new IEParticle();
	particle->Initialization(textureName);
	return particle;
}

bool IEParticle::Ending()
{
	return false;
}

IE_END