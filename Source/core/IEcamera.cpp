#define __IE_DLL_EXPORTS__
#include "IEcamera.h"

#include "../control/IEkeyboard.h"
#include "../type/IEbaseType.h"

IE_BEGIN

IECamera * IECamera::m_StaticCamera = NULL;

IECamera::IECamera()
{
	m_cameraPosi = IEVector(0.0f, 0.0f);
	m_cameraMode = IEPlayerDriverCameraMode;
}

IECamera::~IECamera()
{

}

void IECamera::Initialization()
{
	//IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyW), this, DIK_W);
	//IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyA), this, DIK_A);
	//IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyS), this, DIK_S);
	//IEKeyboard::Share()->BindKeyboardCallback(IEKeyboardCallback(&IEPlayer::PlayerPressKeyD), this, DIK_D);

	Retain();
}

IECamera * IECamera::Share()
{
	if (m_StaticCamera == NULL)
	{
		m_StaticCamera = new IECamera();
		m_StaticCamera->Initialization();
	}
	return m_StaticCamera;
}

void IECamera::SetCameraMode(IECameraMode cameraMode)
{
	m_cameraMode = cameraMode;
}

bool IECamera::ValidateCameraMode(IECameraMode cameraMode)
{
	if (m_cameraMode == cameraMode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void IECamera::SetCameraPosi(const float &x, const float &y)
{
	m_cameraPosi = IEVector(x, y);
}

void IECamera::SetCameraPosi(IEVector posi)
{
	m_cameraPosi = posi;
}

IEVector IECamera::GetGameraPosition()
{
	return m_cameraPosi;
}

void IECamera::MoveByCamera(float hor, float ver)
{
	m_cameraPosi = m_cameraPosi + IEVector(hor, ver);
}

void IECamera::MoveLeftCamera(float x)
{
	m_cameraPosi.m_x = m_cameraPosi.m_x - x;
}

void IECamera::MoveRightCamera(float x)
{
	m_cameraPosi.m_x = m_cameraPosi.m_x + x;
}

void IECamera::Run()
{
	float pixelLength = ((IEBaseType<float> *)SETTING["PixelLength"])->GetData();
	int multiple_x = (int)(m_cameraPosi.m_x / pixelLength);
	int multiple_y = (int)(m_cameraPosi.m_y / pixelLength);
	float recalPosition_x = multiple_x * pixelLength;
	float recalPosition_y = multiple_y * pixelLength;

	glTranslatef(-recalPosition_x, -recalPosition_y, 0.0f);
}

IE_END