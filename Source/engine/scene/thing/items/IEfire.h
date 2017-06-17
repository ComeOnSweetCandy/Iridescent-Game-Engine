/***********************************
* name     : IEfire.h
* creater  : cosc
* info     : fire
* date     : 2017/4/24
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_FIRE__
#define __IE_FIRE__

#include "../IEthing.h"

IE_BEGIN

class __IE_DLL__ IEFire :public IEThing
{
public:
	IEFire();
	virtual ~IEFire();
	virtual void Initialization(unsigned int thingID, float distance);
	static IEFire * Create(unsigned int thingID, float distance);

protected:
	virtual void Update();
	virtual void DrawNode();
	virtual void DrawLight();
	virtual void DrawFire();

public:
	void SetLightColor(float r, float g, float b, float a);
	void SetLightDistance(float distance);
	void SetLightIntension(float intension);

private:
	IEColor m_lightColor;
	float m_distance;
	float m_intension;
};

IE_END

#endif