/***********************************
* name     : IEcmdAnalyse.h
* creater  : cosc
* info     : command analyse class
* date     : 2016/12/1
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CMD_ANALYSE__
#define __IE_CMD_ANALYSE__

#include "../global/IEstdafx.h"
#include "../type/IEstring.h"

IE_BEGIN

class IECmdAnalyse
{
public:
	IECmdAnalyse();
	~IECmdAnalyse();
	void Initialization();
	static IECmdAnalyse * Share();

public:
	void CommandAnalyse(char * command);
	void FieldAnalyse();

	bool AddCommand();
	bool SetCommand();

private:
	static IECmdAnalyse * m_StaticCmdAnalyse;
	IEString ** m_commandArrays;
};

IE_END

#endif