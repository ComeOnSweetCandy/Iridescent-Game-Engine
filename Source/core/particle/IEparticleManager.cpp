#define __IE_DLL_EXPORTS__
#include "IEparticleManager.h"

IE_BEGIN

IEParticleManager * IEParticleManager::m_particleManager = NULL;

IEParticleManager::IEParticleManager()
{
	m_particles = NULL;
}

IEParticleManager::~IEParticleManager()
{
	if (m_particles)
	{
		m_particles->Release();
	}
}

void IEParticleManager::Initialization()
{
	m_particles = IEContainer::CreateAndRetain();
}

IEParticleManager * IEParticleManager::Share()
{
	if (m_particleManager == NULL)
	{
		m_particleManager = new IEParticleManager();
		m_particleManager->Initialization();
	}
	return m_particleManager;
}

void IEParticleManager::PushParticle(IEParticle * particle)
{
	if (particle)
	{
		m_particles->Push(particle);
	}
}

IE_END