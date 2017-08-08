/***********************************
* name     : IEActionAttack.h
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

class __IE_DLL__ IEActionAttack :public IEAction
{
public:
	IEActionAttack();
	virtual ~IEActionAttack();
	virtual void Initialization();
	static IEActionAttack * Create();

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	bool m_haveAttacked;
	float m_lastedTime;
};

IE_END

#endif