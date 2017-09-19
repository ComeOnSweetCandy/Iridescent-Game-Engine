#define __IE_DLL_EXPORTS__
#include "IEphysicNode.h"

#include "IEphysicWorld.h"
#include "../core/IEnode.h"
#include "../interface/cmd/IEapplication.h"

IE_BEGIN

IEPhysicNode::IEPhysicNode()
{
	m_physicEdge = NULL;
	m_node = NULL;
	m_state = __physic_state_static__;

	m_position = 0.0f;
	m_forward = 0.0f;
}

IEPhysicNode::~IEPhysicNode()
{
	UnbindNode();
	ClearPhysicEdge();
}

void IEPhysicNode::Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType)
{
	IEPhysicNode::SetPhysicEdge(physicEdge);
	IEPhysicNode::SetPhysicNodeType(physicNodeType);
}

void IEPhysicNode::Initialization(IEXml * physicXML)
{
	IEPhysicNode::SetPhysicProperty(physicXML);
}

IEPhysicNode * IEPhysicNode::Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicType)
{
	if (physicType == __physic_none_node__)
	{
		return NULL;
	}
	else
	{
		IEPhysicNode * object = new IEPhysicNode();
		object->Initialization(physicEdge, physicType);
		return object;
	}
}

IEPhysicNode * IEPhysicNode::Create(IEXml * physicXML)
{
	IEPhysicNode * object = new IEPhysicNode();
	object->Initialization(physicXML);
	return object;
}

void IEPhysicNode::BindNode(IENode * node)
{
	if (node == NULL)
	{
		if (m_node == NULL)
		{
			__IE_WARNING__("IEPhysicNode : warning . m_node deserve equal null.\n");
		}
		else
		{
			m_node = node;
			UnbindToWorld();
		}
	}
	else
	{
		if (m_node != NULL)
		{
			__IE_WARNING__("IEPhysicNode : warning . m_node deserve not equal null.\n");
		}
		else
		{
			m_node = node;
			BindToWorld();
		}
	}
}

void IEPhysicNode::UnbindNode()
{
	if (m_node)
	{
		m_node->SetPhysicNode(NULL);
		m_node = NULL;
	}
}

IENode * IEPhysicNode::GetBindedNode()
{
	if (m_node == NULL)
	{
		//__IE_WARNING__("IEPhysicNode : warning.\n");
	}

	return m_node;
}

void IEPhysicNode::BindToWorld()
{
	IEApplication::Share()->GetCurrentActiveScene()->GetPhysicWorld()->AddPhysicNode(this);
}

void IEPhysicNode::UnbindToWorld()
{
	IEApplication::Share()->GetCurrentActiveScene()->GetPhysicWorld()->DeletePhysicNode(this);
}

void IEPhysicNode::SetPhysicEdge(IEPhysicEdge * edge)
{
	ClearPhysicEdge();

	m_physicEdge = edge;
	m_physicEdge->Retain();
}

IEPhysicEdge * IEPhysicNode::GetPhysicEdge()
{
	return m_physicEdge;
}

void IEPhysicNode::ClearPhysicEdge()
{
	if (m_physicEdge != NULL)
	{
		m_physicEdge->Release();
		m_physicEdge = NULL;
	}
}

void IEPhysicNode::Collision(IEPhysicNode * physicNode)
{
	IENode * collisionNode = physicNode->GetBindedNode();
	m_node->InteractiveNode(collisionNode);
}

void IEPhysicNode::Collision(IEPhysicNode * physicNode, void * info)
{

}

void IEPhysicNode::DrawPhysicNode()
{
	glPushMatrix();
	glTranslatef(m_position.m_x, m_position.m_y, 0.0f);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float a = 0.4f;
	switch (m_collisionState)
	{
	case IridescentEngine::__collision_safe__:
		glColor4f(0.0f, 1.0f, 0.0f, a);
		break;
	case IridescentEngine::__collision_warning__:
		glColor4f(1.0f, 1.0f, 0.0f, a);
		break;
	case IridescentEngine::__collision_boom__:
		glColor4f(1.0f, 0.0f, 0.0f, a);
		break;
	default:
		break;
	}

	m_physicEdge->DrawPhysicEdge();

	glDisable(GL_BLEND);
	glPopMatrix();
}

void IEPhysicNode::Update()
{
	//总会增加下坠速度
	if (m_physicNodeType == __physic_active_node__)
	{
		m_forward.m_y = m_forward.m_y + (-IEApplication::Share()->GetCurrentActiveScene()->GetPhysicWorld()->m_gravity) * IETime::Share()->GetLastFrapPassingTime();
	}

	if (m_collisionState == __collision_safe__)
	{
		m_state = __physic_state_air__;
	}
	else if (m_collisionState == __collision_warning__)
	{

	}
	else if (m_collisionState == __collision_boom__)
	{
		//如果发生了碰撞 检测反向力的方向 如果是向上 则抵消下坠力量

		//m_state = __physic_state_static__;


	}

	m_displacement = m_displacement + m_forward * IETime::Share()->GetLastFrapPassingTime();
	m_position = m_position + m_displacement;

	m_displacement = 0.0f;
	m_collisionState = __collision_safe__;
}

void IEPhysicNode::SetPhysicProperty(IEXml * physicXML)
{
	IEPhysicNodeType physicType = (IEPhysicNodeType)(physicXML->FindChild("type")->ValueInt());		//读取物理节点的类型
	IEEdgeType edgeType = (IEEdgeType)(physicXML->FindChild("edge")->ValueInt());					//读取物理刚体的类型
	float barycenterOffsetX = physicXML->FindChild("barycenterX")->ValueFloat();					//读取中心点偏移
	float barycenterOffsetY = physicXML->FindChild("barycenterY")->ValueFloat();					//读取中心点偏移
	IEString * infos = physicXML->FindChild("info")->Value();										//获取信息

	//读取物理边缘的信息
	const char * edgeInfo = physicXML->FindChild("info")->ValueString();

	//建立edge
	IEPhysicEdge * physicEdge;
	if (edgeType == __edge_circle__)
	{
		physicEdge = IEPhysicCircle::Create(edgeType, barycenterOffsetX, barycenterOffsetY, infos);
	}
	else if (edgeType == __edge_polygon__)
	{
		physicEdge = IEPhysicPolygon::Create(edgeType, barycenterOffsetX, barycenterOffsetY, infos);
	}
	else
	{
		physicEdge = NULL;
		__IE_ERROR__("IEPhysicNode : error. wrong physic edge type.\n");
	}

	SetPhysicEdge(physicEdge);
	SetPhysicNodeType(physicType);
}

void IEPhysicNode::SetPhysicNodeState(IEPhysicNodeState physicNodeState)
{
	m_state = physicNodeState;
}

void IEPhysicNode::SetPhysicPosition(float x, float y)
{
	m_position = IEVector(x, y);
}

IEVector IEPhysicNode::GetPhysicPosition()
{
	return m_position;
}

void IEPhysicNode::SetDisplacement(float x, float y)
{
	m_displacement = IEVector(x, y);
}

void IEPhysicNode::SetForward(float x, float y)
{
	m_forward = IEVector(x, y);
}

IEVector IEPhysicNode::GetDisplacement()
{
	return m_displacement;
}

void IEPhysicNode::FixPosition()
{
	if (m_physicNodeType == __physic_active_node__)
	{
		m_node->SetTranslate(m_position.m_x, m_position.m_y);
	}
}

IEVector IEPhysicNode::GetBarycenter()
{
	return GetPhysicPosition() + m_physicEdge->GetBarycenter();
}

IEPhysicNodeState IEPhysicNode::GetPhysicState()
{
	return m_state;
}

void IEPhysicNode::SetPhysicNodeType(IEPhysicNodeType physicNodeType)
{
	m_physicNodeType = physicNodeType;

#define PHYSIC_NODE_NONE_MASK				0x0							//00000000 00000000 00000000 00000000
#define PHYSIC_NODE_ACTIVE_MASK				0x1							//00000000 00000000 00000000 00000001
#define PHYSIC_NODE_STATIC_MASK				0x2							//00000000 00000000 00000000 00000010
#define PHYSIC_NODE_AIR_MASK				0x4							//00000000 00000000 00000000 00000100
#define PHYSIC_NODE_MINE_AIR_MASK			0x8							//00000000 00000000 00000000 00001000

#define PHYSIC_NODE_NONE_OPERA				0x0							//00000000 00000000 00000000 00000000
#define PHYSIC_NODE_ACTIVE_OPERA			0x2							//00000000 00000000 00000000 00000010
#define PHYSIC_NODE_STATIC_OPERA			0x0							//00000000 00000000 00000000 00000000
#define PHYSIC_NODE_AIR_OPERA				0x1							//00000000 00000000 00000000 00000001
#define PHYSIC_NODE_MINE_AIR_OPERA			0x0							//00000000 00000000 00000000 00000000

	//进行掩码与操作数的判定
	switch (physicNodeType)
	{
	case IridescentEngine::__physic_none_node__:
		m_mask = PHYSIC_NODE_NONE_MASK;
		m_opera = PHYSIC_NODE_NONE_OPERA;
		break;
	case IridescentEngine::__physic_active_node__:
		m_mask = PHYSIC_NODE_ACTIVE_MASK;
		m_opera = PHYSIC_NODE_ACTIVE_OPERA;
		break;
	case IridescentEngine::__physic_static_node__:
		m_mask = PHYSIC_NODE_STATIC_MASK;
		m_opera = PHYSIC_NODE_STATIC_OPERA;
		break;
	case IridescentEngine::__physic_air_node__:
		m_mask = PHYSIC_NODE_AIR_MASK;
		m_opera = PHYSIC_NODE_AIR_OPERA;
		break;
	case IridescentEngine::__physic_mine_air_node__:
		m_mask = PHYSIC_NODE_AIR_MASK;
		m_opera = PHYSIC_NODE_AIR_OPERA;
		break;
	default:
		break;
	}
}

IEPhysicNodeType IEPhysicNode::GetPhysicNodeType()
{
	return m_physicNodeType;
}

IE_END