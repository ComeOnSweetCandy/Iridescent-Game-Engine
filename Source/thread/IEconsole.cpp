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

		//��Ϊ����һ���߳��� ���е�opengl����������Ч�� ���Խ�����ע���б��� һ����ȡһ��������н���
		IECmdAnalyse::Share()->InjuectCommand(strCommand);
	}
}

IE_END