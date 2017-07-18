#define __IE_DLL_EXPORTS__
#include "IEconsole.h"

IE_BEGIN

IEConsole * IEConsole::m_StaticConsole = NULL;

IEConsole::IEConsole()
{

}

IEConsole::~IEConsole()
{

}

void IEConsole::Initialization()
{
	IEThreadProtocol::Initialization();
}

IEConsole * IEConsole::Share()
{
	if (m_StaticConsole == NULL)
	{
		m_StaticConsole = new IEConsole();
	}
	return m_StaticConsole;
}

void MainLoop()
{
	glutSwapBuffers();
}

void IEConsole::Thread()
{
	char strCommand[256];
	char chReturn;

	printf(">");

	while (true)
	{
		scanf("%[0-9a-zA-Z _]s", strCommand, &chReturn);
		fflush(stdin);

		//因为在另一个线程下 所有的opengl操作都是无效的 所以将命令注入列表中 一次提取一个命令进行解析
		IECmdAnalyse::Share()->InjuectCommand(strCommand);
	}
}

IE_END