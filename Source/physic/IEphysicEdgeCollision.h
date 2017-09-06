/***********************************
* name     : IEphysicEdgeCollision.h
* creater  : cosc
* info     : collision check
* date     : 2017/1/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PHYSIC_EDGE_COLLISION__
#define __IE_PHYSIC_EDGE_COLLISION__

#include "IEphysicNode.h"
#include "physicEdge/IEphysicCircle.h"
#include "physicEdge/IEphysicPolygon.h"
#include "physicEdge/IEphysicSector.h"

IE_BEGIN

class __IE_DLL__ IEPhysicEdgeCollision
{
public:
	static IEPhysicCollisionState EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &axis, float &t);			//Ψһ�ӿ�

private:
	inline static IEPhysicCollisionState CollisionPolygonPolygon(IEPhysicNode * nodeA, IEPhysicNode * nodeB);				//����� �����
	inline static IEPhysicCollisionState CollisionCircleCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB);					//Բ Բ
	inline static IEPhysicCollisionState CollisionPolygonCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB);				//����� Բ

	/*
	** ��������һЩͨ�õĽӿ�
	*/

	//����һ���������һ���������ϵ�ͶӰ �ļ���Сֵ
	inline static void GetPolygonInterval(const IEVector * vertexs, unsigned int vertexsNum, const IEVector &axis, float &min, float &max);

	//����һ��Բ����һ���������ϵ�ͶӰ�� ����Сֵ
	inline static void GetCircleInterval(float radius, const IEVector &axis, float &min, float &max);

	//����Ƿ��������� �⼴ ������ͬһ�����ϵļ�ֵ��Χ ��ǰ�Ƿ��ཻ��������ཻ�����涨ʱ�����Ƿ��ཻ���ཻ��ʱ���Ϊ���١����շ��ص���������ֵ֮��Ĳ�ֵ��ͶӰ��ֵ��
	inline static bool IntervalIntersect(float min0, float max0, float min1, float max1, const IEVector &axis, const IEVector &distance, const IEVector &displacement, float &taxis, float tmax);

	//�����ǰ�ཻ �ҵ����� ���δ���ཻ ����ʱ��
	inline static bool FindMTD();

public:
	static IEVector _CacheN;			//��¼���� ��Ϊ����ֵ
	static float _CacheT;				//ʱ������Ǿ��� ��Ϊ����ֵ

	static IEVector _Axis[64];			//��¼���еķ�������
	static unsigned int _NumAxis;		//��¼һ���ж��ٸ�����
	static float _Taxis[64];			//һ������ǵ�ǰ�ཻ ���Ǽ�¼�ڷ��������� ����λ��֮��Ĳ��ֵ ��ʱΪ��ֵ ���������δ���ཻ ���Ǽ�¼ʱ��ֵ
};

IE_END

#endif