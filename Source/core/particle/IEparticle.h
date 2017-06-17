/***********************************
* name     : IEparticle.h
* creater  : cosc
* info     : particle base class
* date     : 2017/3/2
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PARTICLE__
#define __IE_PARTICLE__

#include "../../core/element/IEsprite.h"

IE_BEGIN

class __IE_DLL__ IEParticle :public IESprite
{
public:
	IEParticle();
	virtual ~IEParticle();
	virtual void Initialization(char * textureName);
	static IEParticle * Create(char * textureName);

public:
	bool Ending();

private:
	friend class IEParticleManager;
};

IE_END

#endif