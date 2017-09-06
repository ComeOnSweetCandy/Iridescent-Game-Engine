/***********************************
* name     : IEphysicPolygon.h
* creater  : cosc
* info     : physic nodes' edge polygon
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_POLYGON__
#define __IE_PHYSIC_POLYGON__

#include "IEphysicEdge.h"
#include "../../type/IEstring.h"

IE_BEGIN

class __IE_DLL__ IEPhysicPolygon :public IEPhysicEdge
{
public:
	IEPhysicPolygon();
	virtual ~IEPhysicPolygon();
	virtual void Initialization(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos);
	static IEPhysicPolygon * Create(IEEdgeType edgeType, float barycenterX, float barycenterY, IEString * infos);

public:
	virtual void DrawPhysicEdge();

private:
	void SetVertexs(IEString * infos);

private:
	IEVector * m_vertexs;				//�洢���еĵ��λ��
	unsigned int m_vertexsNum;			//һ���ж��ٸ��߽�

	friend class IEPhysicEdgeCollision;
};

IE_END

#endif