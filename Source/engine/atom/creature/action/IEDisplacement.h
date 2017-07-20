/***********************************
* name     : IEdisplacement.h
* creater  : cosc
* info     : action displacement
* c_date   : 2017/2/17
* l_date   : 2017/2/17
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_DISPLACEMENT__
#define __IE_DISPLACEMENT__

#include "IEaction.h"

IE_BEGIN

class __IE_DLL__ IEDisplacement :public IEAction
{
public:
	IEDisplacement();
	virtual ~IEDisplacement();
	virtual void Initialization(float x, float y);
	virtual void Initialization(int x, int y);
	static IEDisplacement * Create();
	static IEDisplacement * Create(float x, float y);
	static IEDisplacement * Create(int x, int y);

public:
	virtual bool Begin();
	virtual bool Excute();
	virtual bool End();

private:
	void SetActionNodeDisplacement();
	void SetActionNodeFaceDirection();
	void SetTextureDirection();

	void SetDirection(int x, int y);
	void SetDisplacement(float x, float y);

private:
	IEVector m_displacement;
	IEGrid m_direction;
};

IE_END

#endif