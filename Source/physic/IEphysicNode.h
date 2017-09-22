/***********************************
* name     : IEphysicNode.h
* creater  : cosc
* info     : physic node
* date     : 2016/12/9
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_NODE__
#define __IE_PHYSIC_NODE__

#include "../core/IEobject.h"
#include "physicEdge/IEphysicEdge.h"
#include "../tools/IEXml.h"

IE_BEGIN

class IEPhysicWorld;
class IENode;

enum __IE_DLL__ IEPhysicCollisionState
{
	__collision_safe__,
	__collision_warning__,
	__collision_boom__
};

enum __IE_DLL__ IEPhysicNodeState
{
	__physic_state_static__,
	__physic_state_air__
};

enum __IE_DLL__ IEPhysicNodeType
{
	__physic_none_node__,				//不参与计算
	__physic_active_node__,				//活动的物理节点
	__physic_static_node__,				//静止不动的物理节点
	__physic_air_node__,				//空气型物理体
	__physic_suspend_node__,			//悬浮型物理节点
};

class __IE_DLL__ IEPhysicNode :public IEObject
{
public:
	IEPhysicNode();
	virtual ~IEPhysicNode();
	virtual void Initialization(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType);
	virtual void Initialization(IEXml * physicXML);
	static IEPhysicNode * Create(IEPhysicEdge * physicEdge, IEPhysicNodeType physicNodeType);
	static IEPhysicNode * Create(IEXml * physicXML);

private:
	virtual void Update();
	virtual void Collision(IEPhysicNode * physicNode);
	virtual void Collision(IEPhysicNode * physicNode, void * info);
	virtual void DrawPhysicNode();

public:
	void BindToWorld();
	void UnbindToWorld();

	void BindNode(IENode * node);
	void UnbindNode();
	IENode * GetBindedNode();

	void SetPhysicProperty(IEXml * physicXML);								//更改physic的属性
	void SetPhysicNodeState(IEPhysicNodeState physicNodeState);					//设定当前physicNode的状态

	void SetPhysicNodeType(IEPhysicNodeType physicNodeType);				//设定物理节点的类型
	IEPhysicNodeType GetPhysicNodeType();

	void SetPhysicEdge(IEPhysicEdge * edge);								//设定物理节点的形状
	IEPhysicEdge * GetPhysicEdge();
	void ClearPhysicEdge();
	IEVector GetBarycenter();
	IEPhysicNodeState GetPhysicState();					//获取物理体当前的状态

	void SetPhysicPosition(float x, float y);
	void SetDisplacement(float x, float y);
	void SetSpeed(float speed);
	void SetForward(float x, float y);

	IEVector GetPhysicPosition();
	IEVector GetDisplacement();
	void FixPosition();

protected:
	IEVector m_position;								//当前的位置
	IEVector m_forward;									//朝某个方向的动力
	IEVector m_displacement;							//由node设置的displacement并不计入物理体的运动 此时为static

	IENode * m_node;									//绑定的node元素
	IEPhysicEdge * m_physicEdge;						//物理体的外形类型
	IEPhysicNodeType m_physicNodeType;					//物理体的类型
	IEPhysicCollisionState m_collisionState;			//当前的碰撞状态
	IEPhysicNodeState m_state;							//当前处于的状态

	unsigned short m_mask;
	unsigned short m_opera;

	friend class IEPhysicWorld;
	friend class IEPhysicEdgeCollision;
};

IE_END

#endif