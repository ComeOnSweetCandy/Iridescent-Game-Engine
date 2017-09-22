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
	__physic_none_node__,				//���������
	__physic_active_node__,				//�������ڵ�
	__physic_static_node__,				//��ֹ����������ڵ�
	__physic_air_node__,				//������������
	__physic_suspend_node__,			//����������ڵ�
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

	void SetPhysicProperty(IEXml * physicXML);								//����physic������
	void SetPhysicNodeState(IEPhysicNodeState physicNodeState);					//�趨��ǰphysicNode��״̬

	void SetPhysicNodeType(IEPhysicNodeType physicNodeType);				//�趨����ڵ������
	IEPhysicNodeType GetPhysicNodeType();

	void SetPhysicEdge(IEPhysicEdge * edge);								//�趨����ڵ����״
	IEPhysicEdge * GetPhysicEdge();
	void ClearPhysicEdge();
	IEVector GetBarycenter();
	IEPhysicNodeState GetPhysicState();					//��ȡ�����嵱ǰ��״̬

	void SetPhysicPosition(float x, float y);
	void SetDisplacement(float x, float y);
	void SetSpeed(float speed);
	void SetForward(float x, float y);

	IEVector GetPhysicPosition();
	IEVector GetDisplacement();
	void FixPosition();

protected:
	IEVector m_position;								//��ǰ��λ��
	IEVector m_forward;									//��ĳ������Ķ���
	IEVector m_displacement;							//��node���õ�displacement����������������˶� ��ʱΪstatic

	IENode * m_node;									//�󶨵�nodeԪ��
	IEPhysicEdge * m_physicEdge;						//���������������
	IEPhysicNodeType m_physicNodeType;					//�����������
	IEPhysicCollisionState m_collisionState;			//��ǰ����ײ״̬
	IEPhysicNodeState m_state;							//��ǰ���ڵ�״̬

	unsigned short m_mask;
	unsigned short m_opera;

	friend class IEPhysicWorld;
	friend class IEPhysicEdgeCollision;
};

IE_END

#endif