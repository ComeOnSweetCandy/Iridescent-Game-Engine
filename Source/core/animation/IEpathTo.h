/***********************************
* name     : IEPathToTo.h
* creater  : cosc
* info     : cal grid path to
* date     : 2016/12/14
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PATH_TO__
#define __IE_PATH_TO__

#include "IEanimation.h"
#include "../IEnode.h"
#include "../container/IEcontianer.h"

IE_BEGIN

class IEPathTo :public IEAnimation
{
public:
	IEPathTo(IEArray * paths);
	virtual ~IEPathTo();
	virtual void Initialization();
	static IEPathTo * Create(IEArray * paths);

public:
	virtual bool Run(IENode * node);
	virtual void CompletedAction(IENode * node);
	virtual void SetCircle();
	virtual void SetLoop();

public:
	void ClearCurPath(IENode * node);

private:
	IEArray * m_paths;
	int m_curPathIndex;
	float m_course;
	IEVector m_vDistance;
	IEVector m_startPosi;
};

IE_END

#endif