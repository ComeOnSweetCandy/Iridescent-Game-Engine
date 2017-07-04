/***********************************
* name     : IEwater.h
* creater  : cosc
* info     : terrain grid water
* date     : 2017/4/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_WATER__
#define __IE_WATER__

#include "../IETerrain.h"

IE_BEGIN

class __IE_DLL__ IEWater :public IETerrain
{
public:
	IEWater();
	virtual ~IEWater();
	virtual void Initialization(char * textureName);
	static IEWater * Create(char * textureName);

protected:
	virtual void DrawNode();

private:
	void LoadShader();
};

IE_END

#endif