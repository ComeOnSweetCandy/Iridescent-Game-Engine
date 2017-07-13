/***********************************
* name     : IEcamera.h
* creater  : cosc
* info     : only one camera
* date     : 2016/12/13
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CAMERA__
#define __IE_CAMERA__

#include "IEobject.h"
#include "../type/IEvector.h"

IE_BEGIN

class IEKeyboard;

enum IECameraMode
{
	IEPlayerDriverCameraMode,
	IEGodViewCameraMode
};

class __IE_DLL__ IECamera :public IEObject
{
public:
	IECamera();
	virtual ~IECamera();
	virtual void Initialization();
	static IECamera * Share();

public:
	void SetCameraPosi(const float &x, const float &y);
	void SetCameraPosi(IEVector posi);
	IEVector GetGameraPosition();
	void MoveLeftCamera(float x);
	void MoveRightCamera(float x);
	void MoveByCamera(float hor, float ver);
	void Run();

public:
	void SetCameraMode(IECameraMode cameraMode);
	bool ValidateCameraMode(IECameraMode cameraMode);

private:
	static IECamera * m_StaticCamera;
	IEVector m_cameraPosi;
	IECameraMode m_cameraMode;

	bool m_cameraMoveLiner;
	IEVector m_cameraSpeed;
};

IE_END

#endif