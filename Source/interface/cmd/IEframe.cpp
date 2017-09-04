#define __IE_DLL_EXPORTS__
#include "IEframe.h"
#include "IEapplication.h"

#include "../../type/IEbaseType.h"

IE_BEGIN

IEFrame * IEFrame::m_StaticFrame = NULL;

IEFrame::IEFrame()
{

}

IEFrame::~IEFrame()
{

}

void IEFrame::Release()
{
	delete this;
}

void IEFrame::Initialization()
{

}

IEFrame * IEFrame::Share()
{
	if (m_StaticFrame == NULL)
	{
		m_StaticFrame = new IEFrame();
		m_StaticFrame->Initialization();
	}
	return m_StaticFrame;
}

void IEFrame::CreateOpenglWindow(int &argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	ChangeSize(1200, 800);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("IEapplilcation");
	glewInit();

	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyPressFunc);
	glutDisplayFunc(MainLoop);

	Setup();

	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
}

void IEFrame::MainLoop()
{
	IEApplication::Share()->ApplicationLoop();

	glutSwapBuffers();
}

void IEFrame::Setup()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_ALPHA_TEST);

	IEApplication::Share()->DefaultSetup();
}

void IEFrame::ChangeSize(int w, int h)
{
	GLfloat windowWidth;
	GLfloat windowHeight;

	if (h == 0)
		h = 1;

	if (w <= h)
	{
		windowHeight = IESituation::Share()->_FieldAltitude * (GLfloat)h / (GLfloat)w;
		windowWidth = IESituation::Share()->_FieldAltitude;
	}
	else
	{
		windowWidth = IESituation::Share()->_FieldAltitude * (GLfloat)w / (GLfloat)h;
		windowHeight = IESituation::Share()->_FieldAltitude;
	}

	SETTING.DeleteEntry("ScreenSize");
	SETTING.DeleteEntry("PixelLength");
	SETTING["ScreenSize"] = IEGrid::Create(w, h);
	SETTING["PixelLength"] = new IEBaseType<float>(windowHeight * 2 / h);

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-windowWidth, windowWidth, -windowHeight, windowHeight);
	//glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//进行一些基本设置
	HWND hwnd = GetActiveWindow();
	IESituation::Share()->_Hwnd = hwnd;

	tagRECT clientRect;
	GetClientRect(hwnd, &clientRect);
	IESituation::Share()->_ScreenWidth = clientRect.right - clientRect.left;
	IESituation::Share()->_ScreenHeight = clientRect.bottom - clientRect.top;
}

void IEFrame::TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(3, TimerFunction, 1);
}

void IEFrame::KeyPressFunc(unsigned char key, int x, int y)
{

}

IE_END
