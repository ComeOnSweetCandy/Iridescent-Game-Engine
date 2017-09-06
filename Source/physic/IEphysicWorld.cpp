#define __IE_DLL_EXPORTS__
#include "IEphysicWorld.h"

#include "../core/IEnode.h"
#include "../core/container/IEcontianer.h"

IE_BEGIN

IEPhysicWorld::IEPhysicWorld()
{
	m_physicNodeArrays = NULL;
	m_displayPhysicNode = false;
}

IEPhysicWorld::~IEPhysicWorld()
{
	__IE_RELEASE__(m_physicNodeArrays);
}

void IEPhysicWorld::Initialization()
{
	m_physicNodeArrays = IEContainer::CreateAndRetain();
}

IEPhysicWorld * IEPhysicWorld::Create()
{
	IEPhysicWorld * physicWorld = new IEPhysicWorld();
	physicWorld->Initialization();
	return physicWorld;
}

void IEPhysicWorld::Run()
{
	IEPhysicNode ** physicNodes = (IEPhysicNode **)(m_physicNodeArrays->GetContainer());
	int physicNodesCount = m_physicNodeArrays->Count();

	//physic node update
	for (int index = 0; index < physicNodesCount; index++)
	{
		IEPhysicNode *physicNode = (IEPhysicNode *)physicNodes[index];
		if (physicNode)
		{
			physicNode->Update();
		}
	}

	for (int a_index = 0; a_index < physicNodesCount; a_index++)
	{
		IEPhysicNode * physicNode1 = physicNodes[a_index];

		for (int b_index = a_index + 1; b_index < physicNodesCount; b_index++)
		{
			IEPhysicNode * physicNode2 = physicNodes[b_index];

			if (physicNode1 == NULL || physicNode2 == NULL)
			{
				//如果为空
				continue;
			}

			if (!(physicNode1->m_opera & physicNode2->m_mask) && !(physicNode2->m_opera & physicNode1->m_mask))
			{
				//没有必要的碰撞计算
				continue;
			}

			IEVector N = IEVector(0.0f, 0.0f);
			float t = 1.0f;
			IEPhysicCollisionState collisionState = IEPhysicEdgeCollision::EdgeCoincidence(physicNode1, physicNode2, N, t);

			physicNode1->m_collisionState = collisionState > physicNode1->m_collisionState ? collisionState : physicNode1->m_collisionState;
			physicNode2->m_collisionState = collisionState > physicNode2->m_collisionState ? collisionState : physicNode2->m_collisionState;

			if (collisionState == __collision_safe__)
			{

			}
			else if (collisionState == __collision_warning__)
			{
				
			}
			else if (collisionState == __collision_boom__)
			{
				if (t < 0.0f)
				{
					//如果是active static 纠正位置
					ProcessOverlap(physicNode1, physicNode2, N * -t);
				}

				//这里进行判断 是谁撞的谁
				if (physicNode1->m_opera & physicNode2->m_mask)
				{
					physicNode1->Collision(physicNode2);
				}
				else
				{
					physicNode2->Collision(physicNode1);
				}
			}
		}
	}

	//physicNode draw
	for (int index = 0; index < physicNodesCount; index++)
	{
		IEPhysicNode * physicNode = (IEPhysicNode *)physicNodes[index];
		if (physicNode)
		{
			physicNode->FixPosition();
		}
	}

	if (GetDisplayPhysicNode())
	{
		for (int index = 0; index < physicNodesCount; index++)
		{
			IEPhysicNode * physicNode = (IEPhysicNode *)physicNodes[index];
			if (physicNode)
			{
				physicNode->DrawPhysicNode();
			}
		}
	}

	m_physicNodeArrays->CleanSpace();
}

void IEPhysicWorld::ProcessCollision(IEPhysicNode * a, IEPhysicNode * b, IEVector& N, float t)
{
	float s_fFriction = 0.0f;
	float s_fGlue = 0.0f;
	float s_fRestitution = 0.0f;

	IEVector D = a->m_position - b->m_position;
	float n = D * N;
	IEVector Dn = N * n;
	IEVector Dt = D - Dn;

	if (n > 0.0f) Dn = IEVector(0, 0);

	float dt = Dt * Dt;
	float CoF = s_fFriction;

	if (dt < s_fGlue*s_fGlue) CoF = 1.00f;

	D = -(1.0f + s_fRestitution) * Dn - (CoF)* Dt;

	a->m_position = a->m_position - D * 1.0f;
	b->m_position = b->m_position + D * 0.0f;
}

void IEPhysicWorld::ProcessOverlap(IEPhysicNode * a, IEPhysicNode * b, IEVector& xMTD)
{
	if (a->m_physicNodeType == __physic_active_node__ && b->m_physicNodeType == __physic_static_node__)
	{
		a->m_position = a->m_position + xMTD;
	}
	else if (b->m_physicNodeType == __physic_active_node__ && a->m_physicNodeType == __physic_static_node__)
	{
		b->m_position = b->m_position + xMTD;
	}
	else
	{
		return;
	}
}

void IEPhysicWorld::AddPhysicNode(IEPhysicNode * physicNode)
{
	m_physicNodeArrays->Push(physicNode);
}

void IEPhysicWorld::DeletePhysicNode(IEPhysicNode * physicNode)
{
	m_physicNodeArrays->PopWithClean(physicNode);
}

void IEPhysicWorld::SetDisplayPhysicNode(bool displayPhysicNode)
{
	m_displayPhysicNode = displayPhysicNode;
}

bool IEPhysicWorld::GetDisplayPhysicNode()
{
	return m_displayPhysicNode;
}

IE_END