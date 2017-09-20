#define __IE_DLL_EXPORTS__
#include "IEphysicWorld.h"

#include "../core/IEnode.h"
#include "../core/container/IEcontianer.h"

IE_BEGIN

IEPhysicWorld::IEPhysicWorld()
{
	m_physicNodeArrays = NULL;
	m_displayPhysicNode = true;
	m_gravity = 100.0f;
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

			if (physicNode1->m_opera & physicNode2->m_mask)
			{
				physicNode1->m_collisionState = collisionState > physicNode1->m_collisionState ? collisionState : physicNode1->m_collisionState;
				physicNode1->Collision(physicNode2);
			}
			if (physicNode2->m_opera & physicNode1->m_mask)
			{
				physicNode2->m_collisionState = collisionState > physicNode2->m_collisionState ? collisionState : physicNode2->m_collisionState;
				physicNode2->Collision(physicNode1);
			}

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
			}
		}
	}

	//改变绑定的node元素的位置
	for (int index = 0; index < physicNodesCount; index++)
	{
		IEPhysicNode * physicNode = (IEPhysicNode *)physicNodes[index];
		if (physicNode)
		{
			physicNode->FixPosition();
		}
	}

	m_physicNodeArrays->CleanSpace();
}

void IEPhysicWorld::ProcessOverlap(IEPhysicNode * a, IEPhysicNode * b, IEVector& xMTD)
{
	if (a->m_physicNodeType == __physic_active_node__ && b->m_physicNodeType == __physic_static_node__)
	{
		a->m_position = a->m_position - xMTD;

		//cos(a) = a*b/(|a| * |b|) 求夹角 如果夹角在一定范围内 则抵消forward
		IEVector reverseForward = a->m_forward;
		reverseForward.Reverse();
		auto angle = acos((reverseForward * -xMTD) / (reverseForward.Length() * xMTD.Length()));
		if (angle < 0.2616)
		{
			a->SetForward(0.0f, 0.0f);
			a->m_state = __physic_state_static__;
		}
	}
	else if (b->m_physicNodeType == __physic_active_node__ && a->m_physicNodeType == __physic_static_node__)
	{
		b->m_position = b->m_position + xMTD;

		//cos(a) = a*b/(|a| * |b|) 求夹角 如果夹角在一定范围内 则抵消forward
		IEVector reverseForward = b->m_forward;
		reverseForward.Reverse();
		auto angle = acos((reverseForward * xMTD) / (reverseForward.Length() * xMTD.Length()));
		if (angle < 0.2616)
		{
			b->SetForward(0.0f, 0.0f);
			b->m_state = __physic_state_static__;
		}
	}
	else
	{
		return;
	}
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

void IEPhysicWorld::Draw()
{
	IEPhysicNode ** physicNodes = (IEPhysicNode **)(m_physicNodeArrays->GetContainer());
	int physicNodesCount = m_physicNodeArrays->Count();
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