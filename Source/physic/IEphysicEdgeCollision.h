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
	static IEVector m_cacheN;
	static float m_cacheT;

public:
	static IEPhysicCollisionState EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &xAxis, float &t);

	//多边形 多边形
	inline static IEPhysicCollisionState CollisionPolygonPolygon(IEPhysicNode * a, IEPhysicNode * b);
	inline static bool PP_Collide(const IEVector * A, int Anum, const IEVector* B, int Bnum, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t);

	//圆 圆
	inline static IEPhysicCollisionState CollisionCircleCircle(IEPhysicNode * a, IEPhysicNode * b);
	inline static bool CC_Collide(const float a_radius, const float b_radius, const IEVector &offset, const IEVector &vel, IEVector &N, float &t);
	
	//多边形 圆
	inline static IEPhysicCollisionState CollisionPolygonCircle(IEPhysicNode * a, IEPhysicNode * b);
	inline static bool PC_Collide(const IEVector * A, int Anum,const float b_radius, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t);

	//点 多边形
	inline static IEPhysicCollisionState CollisionPolygonDot(IEPhysicNode * a, IEPhysicNode * b);
	static bool PD_Collide(const IEVector * A, int Anum, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t);

	//点 圆

	inline static bool FindMTD(IEVector * xAxis, float * taxis, int iNumAxes, IEVector &N, float &t);
	inline static bool IntervalIntersect(float min0, float max0, float min1 , float max1, const IEVector &xAxis, const IEVector &xOffset, const IEVector &xVel, float &taxis, float tmax);
	inline static void GetPolygonInterval(const IEVector * axVertices, int iNumVertices, const IEVector &xAxis, float &min, float &max);
	inline static void GetCircleInterval(float radius, const IEVector &xAxis, float &min, float &max);
};

IE_END

#endif