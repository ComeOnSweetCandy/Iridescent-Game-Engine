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
	//printf("build succeed.");
	//static bool ye = true;
	//if (ye)
	//{
	//	ye = false;

	//	int argc = 1;
	//	char * str = "C:\\IridescentEngine\\Debug\\IridescentEngine.exe";
	//	char * argv[1];
	//	argv[0] = str;

	//	glutInit(&argc, argv);
	//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//	glutInitWindowSize(800, 600);
	//	glutCreateWindow("IEapplilcation");
	//	glewInit();

	//	glutDisplayFunc(MainLoop);
	//	//Setup();

	//	//glutTimerFunc(33, TimerFunction, 1);
	//	glutMainLoop();
	//}

	char strCommand[256];
	char chReturn;

	strCommand;
	chReturn;

	while (true)
	{
		printf(">");
		//scanf("%[0-9a-zA-Z ]s", strCommand, &chReturn);
		fflush(stdin);
		IECmdAnalyse::Share()->CommandAnalyse(strCommand);
	}
}

IE_END