/***********************************
* name     : IEtrigger.h
* creater  : cosc
* info     : trigger base class
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

enum IETriggerType
{
	__trigger_collision_type__,
	__trigger_interaction_type__,
	__trigger_type_count__
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

protected:
	virtual bool RunTrigger();
	virtual void Collision(IEPhysicNode * physicNode);

	IEClock * BuildClock(IEClockType clockType, int param);

protected:
	IETriggerType m_triggerType;		   //������������
	IEClock * m_clock;                     //�����ļ�ʱ��
	bool m_allowStrikeRepeat;			   //�Ƿ�����ڵ��ظ�����
	IEContainer * m_strikeNodes;           //�Ѿ��������������Ľڵ�

	friend class IETriggerManager;
};

IE_END

#endif