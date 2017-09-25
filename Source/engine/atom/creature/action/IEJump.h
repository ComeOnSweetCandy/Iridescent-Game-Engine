/***********************************
* name     : IEJump.h
* creater  : cosc
* info     : action jump
* date     : 2017/9/25
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_JUMP__
#define __IE_JUMP__

#include "IEAction.h"

IE_BEGIN

class __IE_DLL__ IEJump :public IEAction
{
public:
	IEJump();
	virtual ~IEJump();
	virtual void Initialization();
	static IEJump * Create();					//���ݷ���ȥ�趨ֵ

public:
	virtual void Begin();
	virtual void Excute();
	virtual void End();

private:
	bool m_jumping;
};

IE_END

#endif