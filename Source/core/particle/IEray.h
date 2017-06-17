/***********************************
* name     : IEray.h
* creater  : cosc
* info     : ray
* date     : 2017/4/26
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PAY__
#define __IE_PAY__

#include "IEparticle.h"

IE_BEGIN

class __IE_DLL__ IERay :public IEParticle
{
public:
	IERay();
	virtual ~IERay();
	virtual void Initialization(char * textureName, float rayLength, float rayRotaf);
	static IERay * Create(char * textureName, float rayLength, float rayRotaf);

public:
	void SetRayLength(float rayLength);
	void SetRayRotate(float rayRotate);

protected:
	virtual void DrawNode();

private:

	float m_rayLength;
	float m_rayWidth;
	float m_rayRotate;

};

IE_END

#endif