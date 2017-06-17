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
	virtual void RemoveChild(IENode * node);				//移除子节点且 塞入自动释放池 并不立即释放 可能要挂到其它父节点下
	virtual void DeleteChild(IENode * node);				//移除子节点且 并立即删除
	virtual void RemoveFromParent();						//从父节点移除 塞入自动释放池 并不立即释放 可能要挂到其它父节点下
	virtual void DeleteFromParent();						//从父节点移除 并立即删除
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