/***********************************
* name     : IEcolor.h
* creater  : cosc
* info     : color rgba
* date     : 2016/12/4
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_COLOR__
#define __IE_COLOR__

#include "../core/IEobject.h"

IE_BEGIN

class __IE_DLL__ IEColor:public IEObject
{
public:
	IEColor();
	IEColor(IEColor &color);
	IEColor(const float &r, const float &g, const float &b);
	IEColor(const float &r, const float &g, const float &b, const float &a);
	virtual ~IEColor();
	virtual void Initialization();
	IEColor * Create();

public:

public:
	float m_r;
	float m_g;
	float m_b;
	float m_a;
};

IE_END

#endif