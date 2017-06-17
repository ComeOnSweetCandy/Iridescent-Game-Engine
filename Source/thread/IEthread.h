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

IE_BEGIN

class IEThreadProtocol
{
public:
	IEThreadProtocol();
	~IEThreadProtocol();
	virtual void Initialization();
	static IEThreadProtocol * Create();

public:
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	virtual void Thread();

private:

};

class IEtoolsProtocol
{
public:
	IEtoolsProtocol();
	~IEtoolsProtocol();

private:
	char * m_toolName;
};

IE_END

#endif