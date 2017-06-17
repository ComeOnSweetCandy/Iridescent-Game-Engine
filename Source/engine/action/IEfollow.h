/***********************************
* name     : IEfollow.h
* creater  : cosc
* info     : Ѱ·�㷨
* date     : 2017/3/15
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FOLLOW__
#define __IE_FOLLOW__

#include "../atom/IEatom.h"
#include "IEaction.h"

IE_BEGIN

class IEFollow:public IEAction
{
public:
	IEFollow();
	virtual ~IEFollow();
	virtual void Initialization(IEAtom * atom);
	static IEFollow * Create(IEAtom * atom);

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

public:
	void SetFollowAtom(IEAtom * atom);

private:
	IEAtom * m_followAtom;
	float m_controllDistance;
};

IE_END

#endif