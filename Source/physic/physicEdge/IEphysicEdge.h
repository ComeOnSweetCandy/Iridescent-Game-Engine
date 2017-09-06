/***********************************
* name     : IEphysicEdge.h
* creater  : cosc
* info     : physic nodes' edge
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_EDGE__
#define __IE_PHYSIC_EDGE__

#include "../../core/IEobject.h"
#include "../../type/IEvector.h"

IE_BEGIN

enum __IE_DLL__ IEEdgeType
{
	__edge_circle__,
	__edge_polygon__,
	__edge_sector__,
	__edge_typeCount__
};

class __IE_DLL__ IEPhysicEdge:public IEObject
{
public:
	IEPhysicEdge();
	virtual ~IEPhysicEdge();
	virtual void Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY);
	static IEPhysicEdge * Create(IEEdgeType edgeType, float barycenterX, float barycenterY);

public:
	virtual void DrawPhysicEdge() = 0;

	IEEdgeType GetEdgeType();					//��ȡ����������
	IEVector& GetBarycenter();					//��ȡ���ĵ�/ƫ�Ƶ�

protected:
	IEEdgeType m_edgeType;						//��������״����
	IEVector m_barycenter;						//�������ĵ�

	friend class IEPhysicEdgeCollision;
};

IE_END

#endif