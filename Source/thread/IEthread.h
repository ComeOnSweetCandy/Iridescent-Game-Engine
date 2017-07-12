/***********************************
* name     : IEthread.h
* creater  : cosc
* info     : thread
* date     : 2016/11/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_THREAD__
#define __IE_THREAD__

#include "../global/IEstdafx.h"

#include "../tools/IEimage.h"

IE_BEGIN

class __IE_DLL__ IEThreadProtocol
{
public:
	IEThreadProtocol();
	~IEThreadProtocol();
	virtual void Initialization();
	static IEThreadProtocol * Create();
	static IEThreadProtocol * Share();

public:
	virtual void Thread();
	static DWORD WINAPI ThreadProc(LPVOID lpParam);

	void ThreadLoadImage(IEImage * image);

private:
	IEContainer * m_jobs;			//待处理事务

	static IEThreadProtocol * m_staticThread;
};

class __IE_DLL__ IEtoolsProtocol
{
public:
	IEtoolsProtocol();
	~IEtoolsProtocol();

private:
	char * m_toolName;
};

IE_END

#endif