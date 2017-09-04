/***********************************
* name     : IEtrigger.h
* creater  : cosc
* info     : 触发器的作用在于 每当一个条件触发 会反馈给相应的节点
* date     : 2017/1/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TRIGGER__
#define __IE_TRIGGER__

#include "../../global/IEstdafx.h"
#include "../../physic/IEphysicNode.h"
#include "clock/IEclock.h"

IE_BEGIN

class IEProp;
class IEFrapClock;
class IEStrikeClock;
class IEContainer;
class IEAtom;

typedef void(IEAtom::*IETrggerStrike)(IEPhysicNode * physicNode);

enum IETriggerType
{
	__trigger_warn_type__,			//警戒类型 在一定范围内就会触发
	__trigger_collision_type__,		//碰撞类型 碰撞了就会触发
	__trigger_interaction_type__,	//互动类型 
	__trigger_type_count__			//计数
};

class __IE_DLL__ IETrigger:public IEPhysicNode
{
public:
	IETrigger();
	virtual ~IETrigger();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param);
	static IETrigger * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param);

public:
	IETriggerType GetTriggerType();
	void SetAllowStrikeRepeat(bool allowStrikeRepeat);
	virtual void ClockTick();
	virtual bool GetClockEnd();
	virtual void SetClockEnd();

	void AddTrigger(IETrggerStrike function, IEAtom * self);

protected:
	virtual bool RunTrigger();
	virtual void Collision(IEPhysicNode * physicNode);

	IEClock * BuildClock(IEClockType clockType, int param);

protected:
	IETriggerType m_triggerType;		   //触发器的类型
	IEClock * m_clock;                     //依附的计时器
	bool m_allowStrikeRepeat;			   //是否允许节点重复触发
	IEContainer * m_strikeNodes;           //已经启动过触发器的节点

	IEAtom * m_attachAtom;
	IETrggerStrike m_callback;

	friend class IETriggerManager;
};

IE_END

#endif