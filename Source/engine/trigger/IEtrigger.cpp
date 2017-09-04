#define __IE_DLL_EXPORTS__
#include "IEtrigger.h"

#include "../atom/IEatom.h"
#include "../atom/IEprop.h"
#include "clock/IEfrapClock.h"
#include "clock/IEstrikeClock.h"
#include "../../core/container/IEcontianer.h"
#include "../../interface/cmd/IEapplication.h"

IE_BEGIN

IETrigger::IETrigger()
{
	m_triggerType = __trigger_type_count__;
	m_clock = NULL;
	m_allowStrikeRepeat = false;
	m_strikeNodes = NULL;
}

IETrigger::~IETrigger()
{
	if (m_clock)
	{
		delete m_clock;
	}
	if (m_strikeNodes)
	{
		m_strikeNodes->Release();
		m_strikeNodes = NULL;
	}
}

void IETrigger::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IEPhysicNode::Initialization(physicEdge, physicNodeType);

	m_clock = BuildClock(clockType, param);
	m_strikeNodes = IEContainer::CreateAndRetain();

	IEApplication::Share()->GetCurrentActiveScene()->GetTriggerManager()->AddTrigger(this);
}

IETrigger * IETrigger::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType, IEClockType clockType, int param)
{
	IETrigger * trigger = new IETrigger();
	trigger->Initialization(physicEdge, physicNodeType, clockType, param);
	return trigger;
}

void IETrigger::ClockTick()
{
	IEProp * prop = (IEProp *)m_node;
	if (prop)
	{
		prop->ClockTick();
	}
}

IETriggerType IETrigger::GetTriggerType()
{
	return m_triggerType;
}

void IETrigger::Collision(IEPhysicNode * physicNode)
{
	//这里随便测试一下
	(m_attachAtom->*m_callback)(physicNode);

	IENode * collisionNode = physicNode->GetBindedNode();
	if (m_allowStrikeRepeat)
	{
		m_node->InteractiveNode(collisionNode);
	}
	else
	{
		IEObject * res = m_strikeNodes->Find(collisionNode);
		if (!res)
		{
			m_strikeNodes->Push(collisionNode);
			m_node->InteractiveNode(collisionNode);
		}
	}
}

bool IETrigger::RunTrigger()
{
	m_clock->Run();
	if (m_clock->IsEnd())
	{
		return true;
	}
	return false;
}

void IETrigger::SetClockEnd()
{
	m_clock->SetEnd();
}

bool IETrigger::GetClockEnd()
{
	return m_clock->IsEnd();
}

void IETrigger::AddTrigger(IETrggerStrike function, IEAtom * self)
{
	BindNode(self);

	m_attachAtom = self;
	m_callback = function;
}

IEClock * IETrigger::BuildClock(IEClockType clockType, int param)
{
	switch (clockType)
	{
	case IridescentEngine::__clock_time_type__:
		return IEFrapClock::Create(param);
		break;
	case IridescentEngine::__clock_strike_times_type__:
		return IEStrikeClock::Create(param);
		break;
	case IridescentEngine::__clock_type_count__:
		return NULL;
		break;
	default:
		return NULL;
		break;
	}
}

void IETrigger::SetAllowStrikeRepeat(bool allowStrikeRepeat)
{
	m_allowStrikeRepeat = allowStrikeRepeat;
}

IE_END