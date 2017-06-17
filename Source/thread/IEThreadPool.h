/***********************************
* name     : IEthreadPool.h
* creater  : cosc
* info     : threads pool
* date     : 2016/12/01
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THREAD_POOL__
#define __IE_THREAD_POOL__

#include "../global/IEstdafx.h"
#include "IEthread.h"

IE_BEGIN

class IEThreadPool
{
public:
	IEThreadPool();
	~IEThreadPool();
	void Initialization();
	static IEThreadPool * Share();

private:
	static IEThreadProtocol * m_threadPool;
};

IE_END

#endif