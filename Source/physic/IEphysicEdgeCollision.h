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
	static IEPhysicCollisionState EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &axis, float &t);			//唯一接口

private:
	inline static IEPhysicCollisionState CollisionPolygonPolygon(IEPhysicNode * nodeA, IEPhysicNode * nodeB);				//多边形 多边形
	inline static IEPhysicCollisionState CollisionCircleCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB);					//圆 圆
	inline static IEPhysicCollisionState CollisionPolygonCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB);				//多边形 圆

	/*
	** 接下来是一些通用的接口
	*/

	//计算一个多边形在一个分离轴上的投影 的极大极小值
	inline static void GetPolygonInterval(const IEVector * vertexs, unsigned int vertexsNum, const IEVector &axis, float &min, float &max);

	//计算一个圆形在一个分离轴上的投影的 极大极小值
	inline static void GetCircleInterval(float radius, const IEVector &axis, float &min, float &max);

	//检测是否发生间隔横断 意即 两段在同一轴线上的极值范围 当前是否相交。如果不相交，最大规定时间内是否相交，相交的时间点为多少。最终返回的是两个极值之间的差值（投影差值）
	inline static bool IntervalIntersect(float min0, float max0, float min1, float max1, const IEVector &axis, const IEVector &distance, const IEVector &displacement, float &taxis, float tmax);

	//如果当前相交 找到反弹 如果未来相交 返回时间
	inline static bool FindMTD();

public:
	static IEVector _CacheN;			//记录方向 作为返回值
	static float _CacheT;				//时间或者是距离 作为返回值

	static IEVector _Axis[64];			//记录所有的分离轴线
	static unsigned int _NumAxis;		//记录一共有多少根轴线
	static float _Taxis[64];			//一、如果是当前相交 就是记录在分离轴线上 两段位置之间的差距值 此时为负值 二、如果是未来相交 就是记录时间值
};

IE_END

#endif