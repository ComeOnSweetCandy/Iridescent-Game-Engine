/***********************************
* name     : IEattack.h
* creater  : cosc
* info     : action attack
* date     : 2017/2/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ATTACK__
#define __IE_ATTACK__

#include "IEaction.h"

IE_BEGIN

class IECreature;

class __IE_DLL__ IEAttack :public IEAction
{
public:
	IEAttack();
	virtual ~IEAttack();
	virtual void Initialization();
	static IEAttack * Create();

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

	virtual void Attack();

private:
	bool m_haveAttacked;
	float m_lastedTime;
};

IE_END

#endif