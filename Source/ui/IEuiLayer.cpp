#define __IE_DLL_EXPORTS__
#include "IEuiLayer.h"

IE_BEGIN

IEUiLayer::IEUiLayer()
{

}

IEUiLayer::~IEUiLayer()
{

}

void IEUiLayer::Initialization()
{
	IEWidget::Initialization();
}

void IEUiLayer::Release()
{
	IEWidget::Release();
}

IEUiLayer * IEUiLayer::Create()
{
	IEUiLayer * uiLayer = new IEUiLayer();
	uiLayer->Initialization();
	return uiLayer;
}

void IEUiLayer::Run()
{
	Visit();
}

void IEUiLayer::Visit()
{
	g_wPosition = IEGrid(0, 0);
	w_position = IEGrid(0, 0);

	if (IEWidget::m_display)
	{
		IEWidget::Visit();
		//IEWidget::RunAnimation();
		//IEUiLayer::ChangeModelMatrix();

		//this->IEWidget::Update();
		//this->IEWidget::VisitChilds();

		//IEUiLayer::RevertModelMatrix();
	}
}

void IEUiLayer::DrawNode()
{

}

void IEUiLayer::ChangeModelMatrix()
{
	m_screenSize = *((IEGrid *)(SETTING["ScreenSize"]));
	SetWidgetSize(m_screenSize.m_x, m_screenSize.m_y);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-m_screenSize.m_x / 2, m_screenSize.m_x / 2, -m_screenSize.m_y / 2, m_screenSize.m_y / 2);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-m_screenSize.m_x / 2 - 1, m_screenSize.m_y / 2 + 1, 0.0f);
	glScalef(1.0f, -1.0f, 1.0f);
}

void IEUiLayer::RevertModelMatrix()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

IE_END