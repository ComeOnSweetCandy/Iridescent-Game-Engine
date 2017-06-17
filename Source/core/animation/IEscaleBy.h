/***********************************
* name     : IEscaleBy.h
* creater  : cosc
* info     : scale By
* date     : 2016/12/7
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SCALE_BY__
#define __IE_SCALE_BY__

#include "../IEnode.h"
#include "IEanimation.h"

IE_BEGIN

class IEScaleBy :public IEAnimation
{
public:
	IEScaleBy(float &terminal, float duration);
	virtual ~IEScaleBy();
	virtual void Initialization();
	static IEScaleBy * Create(float duration, float terminal);

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

	//virtual void SetCircleAndLoop(bool circle = false, bool loop = false);

private:
	float m_scaleBy;
	IEVector m_targetScale;
	IEVector m_terminalScale;
	IEVector m_startScale;
};

IE_END

#endif