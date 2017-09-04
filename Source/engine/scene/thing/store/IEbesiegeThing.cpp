#define __IE_DLL_EXPORTS__
#include "IEbesiegeThing.h"

#include "../../../../physic/physicEdge/IEphysicCircle.h"
#include "../../../trigger/IEinteractionTrigger.h"

IE_BEGIN

IEBesiegeThing::IEBesiegeThing()
{

}

IEBesiegeThing::~IEBesiegeThing()
{

}

void IEBesiegeThing::Initialization(unsigned int thingID)
{
	IEThing::Initialization(0, thingID, 1);

	BindInteractionTrigger();
}

IEBesiegeThing * IEBesiegeThing::Create(unsigned int thingID)
{
	IEBesiegeThing * thing = new IEBesiegeThing();
	thing->Initialization(thingID);
	return thing;
}

void IEBesiegeThing::BindRelatedThing(IEThing * thing)
{
	m_relatedThing = thing;
}

void IEBesiegeThing::InteractiveNode(IENode * strikeNode)
{
	//IECreature * owner = GetPropOwner();
	IECreature * strike = (IECreature *)strikeNode;

	//执行施放函数
	lua_getglobal(m_LUA, "Interaction");
	lua_call(m_LUA, 0, 0);

	//对于绑定的元素进行状态切换
	//m_relatedThing->SwitchStateTo(1);
}

void IEBesiegeThing::DrawNode()
{
	IEThing::DrawNode();
}

void IEBesiegeThing::BindInteractionTrigger()
{
	IEPhysicCircleInfo * in = new IEPhysicCircleInfo();
	in->m_physicEdgeType = __edge_circle__;
	in->m_radius = 1.5f;
	in->m_vertexsCount = 32;

	IEPhysicCircle * attackPhysicEdge = IEPhysicCircle::Create(in);
	m_trigger = IEInteractionTrigger::Create(attackPhysicEdge, __physic_air_node__, __clock_strike_times_type__, 0);

	m_trigger->BindNode(this);
}

void IEBesiegeThing::SetPosition(const float &x, const float &y)
{
	IEThing::SetTranslate(x, y);

	if (m_trigger)
	{
		IEVector p = m_physicNode->GetPhysicPosition();
		m_trigger->SetPhysicPosition(p.m_x + m_size[0], p.m_y + m_size[1] / 2);
	}
}

IE_END