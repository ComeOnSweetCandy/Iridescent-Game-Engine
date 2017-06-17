/***********************************
* name     : IEvertigo.h
* creater  : cosc
* info     : action vertigo
* c_date   : 2017/1/17
* l_date   : 2017/1/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_VERTIGO__
#define __IE_VERTIGO__

#include "IEaction.h"

IE_BEGIN

class __IE_DLL__ IEVertigo :public IEAction
{
public:
	IEVertigo();
	virtual ~IEVertigo();
	virtual void Initialization();
	static IEVertigo * Create();

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

private:
	float m_leftTime;
};

IE_END

#endif