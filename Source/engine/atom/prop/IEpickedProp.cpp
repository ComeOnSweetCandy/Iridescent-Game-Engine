#define __IE_DLL_EXPORTS__
#include "IEpickedProp.h"
#include "../creature/IEplayer.h"

#include "../../../physic/physicEdge/IEphysicCircle.h"
#include "../../trigger/IEcollisionTrigger.h"

IE_BEGIN

IEPickedProp::IEPickedProp()
{
	m_propType = __prop_picked_type__;
}

IEPickedProp::~IEPickedProp()
{

}

void IEPickedProp::Initialization(IETrigger * trigger, int propIndex, int propCount)
{
	IEProp::Initialization(propIndex, trigger);

	SetPropCount(propCount);
	ChangePropTexture("propPicked");
	IESprite::SetUnitPiexls(64);
}

IEPickedProp * IEPickedProp::Create(IETrigger * trigger, int propIndex, int propCount)
{
	IEPickedProp * prop = new IEPickedProp();
	prop->Initialization(trigger, propIndex, propCount);
	return prop;
}

void IEPickedProp::InteractiveNode(IENode * strikeNode)
{
	IENode * ownerNode = GetPropOwner();
	if (strikeNode )
	{
		IEPlayer * player = (IEPlayer *)strikeNode;
		IEPropPack * pack = player->GetPlayersPack();
		pack->InsertProp(this);

		IEProp::ClockTick();
	}
}

void CreatePickedProp(int propIndex, int propCount, float x, float y)
{
	IEPhysicCircleInfo * in = new IEPhysicCircleInfo();
	in->m_physicEdgeType = __edge_circle__;
	in->m_radius = 0.5f;
	in->m_vertexsCount = 32;

	IEPhysicCircle * attackPhysicEdge = IEPhysicCircle::Create(in);
	IECollisionTrigger * collisionTrigger = IECollisionTrigger::Create(attackPhysicEdge, __physic_air_node__, true, true);
	IEPickedProp * pickedProp = IEPickedProp::Create(collisionTrigger, propIndex, propCount);

	pickedProp->SetTranslate(x, y);
	collisionTrigger->SetPhysicPosition(x, y);
}

IE_END