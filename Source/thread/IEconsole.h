/***********************************
* name     : IEconsole.h
* creater  : cosc
* info     : console
* date     : 2016/12/1
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CONSOLE__
#define __IE_CONSOLE__

#include "IEthread.h"
#include "../type/IEstring.h"
#include "../tools/IEcmdAnalyse.h"

IE_BEGIN

class IEConsole :public IEThreadProtocol,public IEtoolsProtocol
{
public:
	IEConsole();
	~IEConsole();
	virtual void Initialization();
	static IEConsole * Share();

public:
	virtual void Thread();

private:
	static IEConsole * m_StaticConsole;
};

IE_END

#endif