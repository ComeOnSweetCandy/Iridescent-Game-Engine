/***********************************
* name     : IEnode.h
* creater  : cosc
* info     : draw nodes
* date     : 2016/11/22
* version  : 1.0
* remark   : drawing base node
************************************/

#ifndef __IE_NODE__
#define __IE_NODE__

#include "../core/IEnodeProtocol.h"
#include "../physic/IEphysicNode.h"
#include "container/IEcontianer.h"

#include "animation/IEanimationNodeProtocol.h"

IE_BEGIN

class __IE_DLL__ IENode :public IEObject, public IENodeProtocol, public IEAnimationNodeProtocol
{
public:
	IENode();
	virtual ~IENode();
	virtual void Initialization();
	static IENode * Create();

public:
	virtual void PreVisit();
	virtual void EndVisit();
	virtual void Visit();
	virtual void VisitChilds();
	virtual void Update();
	virtual void InsertDrawNodes();
	virtual void DrawNode();

	void SetDrawMode(bool drawMode);
	virtual void LoadSavedModelMatrix();

	void CreateChilds();
	virtual void AddChild(IENode * node);
	virtual void RemoveChild(IENode * node);				//�Ƴ��ӽڵ��� �����Զ��ͷų� ���������ͷ� ����Ҫ�ҵ��������ڵ���
	virtual void DeleteChild(IENode * node);				//�Ƴ��ӽڵ��� ������ɾ��
	virtual void RemoveFromParent();						//�Ӹ��ڵ��Ƴ� �����Զ��ͷų� ���������ͷ� ����Ҫ�ҵ��������ڵ���
	virtual void DeleteFromParent();						//�Ӹ��ڵ��Ƴ� ������ɾ��
	virtual void RemoveAllChilds();
	bool HasChild(IENode * node);
	IENode * GetParentNode();
	unsigned int GetNodeIndex();
	IEContainer * GetChilds();

	virtual void BindPhysicNode(IEPhysicNode * physicNode);
	virtual void SetPhysicNode(IEPhysicNode * physicNode);
	IEPhysicNode * GetPhysicNode();
	virtual void InteractiveNode(IENode * node);

protected:
	IENode * m_parent;
	IEContainer * m_childs;
	IEPhysicNode * m_physicNode;

private:
	bool m_DrawMode;
	unsigned int m_nodeIndex;
	static unsigned int m_StaticNodeCount;
	static unsigned int m_StaticActiveNodeCount;
};

typedef void(IENode::*IEWidgetCallback)(IENode * widget);
typedef void(IENode::*IEKeyboardCallback)(unsigned char key);

IE_END

#endif