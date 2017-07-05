#define __IE_DLL_EXPORTS__
#include "IEnode.h"

#include "../interface/cmd/IEapplication.h"

IE_BEGIN

unsigned int IENode::m_StaticNodeCount = 0;
unsigned int IENode::m_StaticActiveNodeCount = 0;

IENode::IENode()
{
	m_nodeIndex = m_StaticNodeCount;
	m_StaticActiveNodeCount++;
	m_StaticNodeCount++;

	m_childs = NULL;
	m_parent = NULL;
	m_DrawMode = true;
}

IENode::~IENode()
{
	RemoveAllChilds();
	BindPhysicNode(NULL);
	m_StaticActiveNodeCount--;

	__IE_RELEASE__(m_childs);
}

void IENode::Initialization()
{
	CreateChilds();
}

IENode * IENode::Create()
{
	IENode * node = new IENode();
	node->Initialization();
	return node;
}

void IENode::PreVisit()
{

}

void IENode::Visit()
{
	if (m_display)
	{
		PreVisit();
		RunAnimation();
		ChangeModelMatrix();
		this->Update();
		if (m_DrawMode)
		{
			this->DrawNode();
		}
		else
		{
			this->InsertDrawNodes();
		}
		this->VisitChilds();
		RevertModelMatrix();
		EndVisit();
	}
}

void IENode::EndVisit()
{

}

void IENode::VisitChilds()
{
	if (m_childs)
	{
		IENode ** container = (IENode **)(m_childs->GetContainer());
		for (int index = 0; index < m_childs->Count(); index++)
		{
			if (container[index])
			{
				container[index]->Visit();
			}
		}
	}
}

void IENode::Update()
{

}

void IENode::DrawNode()
{

}

void IENode::InsertDrawNodes()
{
	SetZIndex(m_translate[1]);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);
	IEApplication::Share()->GetCurrentDrawScene()->AddDrawNode(this);
}

void IENode::LoadSavedModelMatrix()
{
	glLoadMatrixf(m_matrix);
}

void IENode::CreateChilds()
{
	m_childs = IEContainer::CreateAndRetain();
}

void IENode::AddChild(IENode * node)
{
	if (node->m_parent)
	{
		__IE_WARNING__("IENode : error . add child.\n");
		return;
	}
	node->m_parent = this;
	m_childs->Push(node);
}

void IENode::RemoveChild(IENode * node)
{
	node->m_parent = NULL;
	m_childs->PopWithClean(node);
}

void IENode::DeleteChild(IENode * node)
{
	node->m_parent = NULL;
	m_childs->DeleteWithClean(node);
}

void IENode::DeleteFromParent()
{
	if (!m_parent)
	{
		return;
	}
	m_parent->DeleteChild(this);
}

void IENode::RemoveFromParent()
{
	if (!m_parent)
	{
		return;
	}
	//m_parent->RemoveChild(this);
	m_parent->DeleteChild(this);
}

void IENode::RemoveAllChilds()
{
	//__IE_RELEASE__(m_childs);
	if (m_childs)
	{
		m_childs->EmptyContainer();
	}
}

bool IENode::HasChild(IENode * node)
{
	if (m_childs->Count() != 0)
	{
		return true;
	}
	return false;
}

IENode * IENode::GetParentNode()
{
	return m_parent;
}

unsigned int IENode::GetNodeIndex()
{
	return m_nodeIndex;
}

IEContainer * IENode::GetChilds()
{
	return m_childs;
}

void IENode::SetPhysicNode(IEPhysicNode * physicNode)
{
	m_physicNode = physicNode;
}

void IENode::BindPhysicNode(IEPhysicNode * physicNode)
{
	if (physicNode == NULL)
	{
		if (m_physicNode == NULL)
		{
			
		}
		else
		{
			m_physicNode->BindNode(NULL);
			SetPhysicNode(NULL);
		}
	}
	else
	{
		if (m_physicNode != NULL)
		{
			__IE_WARNING__("IENode : warning . m_physicNode deserve not equal null.\n");

			m_physicNode->BindNode(NULL);
			SetPhysicNode(NULL);
		}

		SetPhysicNode(physicNode);
		m_physicNode->BindNode(this);
	}
}

IEPhysicNode * IENode::GetPhysicNode()
{
	if (m_physicNode == NULL)
	{
		return NULL;
	}

	return m_physicNode;
}

void IENode::InteractiveNode(IENode * node)
{

}

void IENode::SetDrawMode(bool drawMode)
{
	m_DrawMode = drawMode;
}

IE_END