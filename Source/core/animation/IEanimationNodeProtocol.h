/***********************************
* name     : IEanimationNodeProtocol.h
* creater  : cosc
* info     : action node protocol
* date     : 2016/12/7
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ACTION_NODE_PROTOCOL__
#define __IE_ACTION_NODE_PROTOCOL__

#include "../../global/IEstdafx.h"
#include "IEanimation.h"

IE_BEGIN

class IENode;

class __IE_DLL__ IEAnimationNodeProtocol
{
public:
	IEAnimationNodeProtocol();
	~IEAnimationNodeProtocol();

protected:
	void RunAnimation();
	void GetActionFromList();

public:
	void GoNextAnimation();
	void StartAnimation();
	void StopAnimation();
	void AbandonCurAnimation();
	void AbandonRestAnimation();
	void ClearAnimations();
	void AddAnimation(IEAnimation * animation);
	void DeleteAnimation(IEAnimation * animation);

private:
	bool m_isAnimationRuning;
	IEAnimation * m_curAnimation;
	IEStack * m_animationList;
};

IE_END

#endif