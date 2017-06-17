#define __IE_DLL_EXPORTS__
#include "IEinteractionThing.h"

#include "../../../../interface/cmd/IEapplication.h"
#include "../IEthingArea.h"

#include "../../../../control/IEkeyboard.h"

#include "../../../../physic/physicEdge/IEphysicCircle.h"
#include "../../../trigger/IEinteractionTrigger.h"

IE_BEGIN

IEInteractionThing::IEInteractionThing()
{

}

IEInteractionThing::~IEInteractionThing()
{
	__IE_RELEASE_DIF__(m_prompt);
}

void IEInteractionThing::Initialization(unsigned int thingID)
{
	IEThing::Initialization(thingID);

	BindInteractionTrigger();
	PormptInitialization();
}

IEInteractionThing * IEInteractionThing::Create(unsigned int thingID)
{
	IEInteractionThing * thing = new IEInteractionThing();
	thing->Initialization(thingID);
	return thing;
}

void IEInteractionThing::PormptInitialization()
{
	m_prompt = IESprite::Create("question/body.png");
	m_prompt->SetTranslate(0.0f, 1.0f);
	m_prompt->SetDisplay(0);

	//IENode::AddChild(m_prompt);
}

void IEInteractionThing::BindRelatedThing(IEThing * thing)
{
	m_relatedThing = thing;
	m_relatedCreatedOrder = thing->GetOrder();
}

void IEInteractionThing::InteractiveNode(IENode * strikeNode)
{
	if (IEKeyboard::Share()->KeyTouch(DIK_E))
	{
		//IECreature * owner = GetPropOwner();
		IECreature * strike = (IECreature *)strikeNode;

		//���ڰ󶨵�Ԫ�ؽ���״̬�л�
		if (this == m_relatedThing)
		{
			this->SwitchState();
		}
		else
		{
			this->SwitchState();

			if (m_relatedThing)
			{
				m_relatedThing->SwitchState();
			}
			else if (m_relatedCreatedOrder)
			{
				//find it

				m_relatedThing = IEApplication::Share()->GetCurrentActiveScene()->GetBindedMap()->GetThing()->FindThingByOrder(m_relatedCreatedOrder);
				m_relatedThing->SwitchState();
			}
		}
	}

	m_prompt->SetDisplay(true);
}

void IEInteractionThing::DrawNode()
{
	IEThing::DrawNode();

	m_prompt->Visit();
}

void IEInteractionThing::EndVisit()
{
	m_prompt->SetDisplay(false);
}

void IEInteractionThing::BindInteractionTrigger()
{
	IEPhysicCircleInfo * in = new IEPhysicCircleInfo();
	in->m_physicEdgeType = __edge_circle__;
	in->m_radius = 1.5f;
	in->m_vertexsCount = 32;

	IEPhysicCircle * attackPhysicEdge = IEPhysicCircle::Create(in);
	m_trigger = IEInteractionTrigger::Create(attackPhysicEdge, __physic_air_node__, __clock_strike_times_type__, 0);

	m_trigger->BindNode(this);
}

void IEInteractionThing::SetPosition(const float &x, const float &y)
{
	IEThing::SetTranslate(x, y);

	if (m_trigger)
	{
		IEVector p = m_physicNode->GetPhysicPosition();
		m_trigger->SetPhysicPosition(p.m_x + m_size[0], p.m_y + m_size[1] / 2);
	}
}

IE_END