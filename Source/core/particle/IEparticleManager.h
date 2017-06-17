/***********************************
* name     : IEparticleManager.h
* creater  : cosc
* info     : particle base class
* date     : 2017/3/2
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PARTICLE_MANAGER__
#define __IE_PARTICLE_MANAGER__

#include "IEparticle.h"

IE_BEGIN

class __IE_DLL__ IEParticleManager
{
public:
	IEParticleManager();
	virtual ~IEParticleManager();
	virtual void Initialization();
	static IEParticleManager * Share();

public:
	void PushParticle(IEParticle * particle);

private:
	static IEParticleManager * m_particleManager;

	IEContainer * m_particles;
};

IE_END

#endif