#define __IE_DLL_EXPORTS__
#include "IEphysicEdgeCollision.h"

IE_BEGIN

IEVector IEPhysicEdgeCollision::m_cacheN = IEVector(0.0f,0.0f);
float IEPhysicEdgeCollision::m_cacheT = 0.0f;

IEPhysicCollisionState IEPhysicEdgeCollision::EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &xAxis, float &t)
{
	IEPhysicEdgeType a_type = a->GetPhysicEdge()->GetEdgeType();
	IEPhysicEdgeType b_type = b->GetPhysicEdge()->GetEdgeType();
	IEPhysicCollisionState result = __collision_safe__;

	m_cacheN = IEVector(0.0f, 0.0f);
	m_cacheT = 1.0f;

	if (a_type == __edge_circle__)
	{
		if (b_type == __edge_circle__)
		{
			result = CollisionCircleCircle(a, b);
		}
		else if (b_type == __edge_polygon__)
		{
			result = CollisionPolygonCircle(b, a);
		}
		else if (b_type == __edge_sector__)
		{
			//result = EdgeCoincidenceCirclePolygon(a, b);
		}
	}
	else if (a_type = __edge_polygon__)
	{
		if (b_type == __edge_circle__)
		{
			result = CollisionPolygonCircle(a, b);
		}
		else if (b_type == __edge_polygon__)
		{
			result = CollisionPolygonPolygon(a, b);
		}
		else if (b_type == __edge_sector__)
		{
			//result = EdgeCoincidenceCircleCircle(b, a);
		}
	}
	else if (a_type = __edge_sector__)
	{
		if (b_type == __edge_circle__)
		{
			//result = CollisionPolygonPolygon(a, b);
		}
		else if (b_type == __edge_polygon__)
		{
			//result = EdgeCoincidenceCircleCircle(b, a);
		}
		else if (b_type == __edge_sector__)
		{
			//result = EdgeCoincidenceCircleCircle(b, a);
		}
	}

	xAxis = m_cacheN;
	t = m_cacheT;

	return result;
}

inline IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonPolygon(IEPhysicNode * a, IEPhysicNode * b)
{
	IEPhysicPolygon * a_edge = ((IEPhysicPolygon *)(a->GetPhysicEdge()));
	IEPhysicPolygon * b_edge = ((IEPhysicPolygon *)(b->GetPhysicEdge()));
	IEPhysicPolygonInfo * a_edge_info = (IEPhysicPolygonInfo *)(a_edge->GetPhysicEdgeInfo());
	IEPhysicPolygonInfo * b_edge_info = (IEPhysicPolygonInfo *)(b_edge->GetPhysicEdgeInfo());

	m_cacheT = 1.0f;
	bool result = IEPhysicEdgeCollision::PP_Collide(a_edge_info->m_vertexs, a_edge_info->m_vertexsCount, b_edge_info->m_vertexs, b_edge_info->m_vertexsCount, b->m_position - a->m_position, a->GetDisplacement() - b->GetDisplacement(), m_cacheN, m_cacheT);
	
	if (result == true)
	{
		if (m_cacheT <= 0.00000f)
		{
			return __collision_boom__;
		}
		else
		{
			return __collision_warning__;
		}
	}
	else
	{
		return __collision_safe__;
	}
}

IEPhysicCollisionState IEPhysicEdgeCollision::CollisionCircleCircle(IEPhysicNode * a, IEPhysicNode * b)
{
	IEPhysicCircle * a_edge = (IEPhysicCircle *)(a->GetPhysicEdge());
	IEPhysicCircle * b_edge = (IEPhysicCircle *)(b->GetPhysicEdge());
	IEPhysicCircleInfo * a_edge_info = (IEPhysicCircleInfo *)(a_edge->GetPhysicEdgeInfo());
	IEPhysicCircleInfo * b_edge_info = (IEPhysicCircleInfo *)(b_edge->GetPhysicEdgeInfo());

	IEVector aPosition = a->m_position + IEVector(a_edge->GetOffsetPosition()[0], a_edge->GetOffsetPosition()[1]);
	IEVector bPosition = b->m_position + IEVector(b_edge->GetOffsetPosition()[0], b_edge->GetOffsetPosition()[1]);

	m_cacheT = 1.0f;
	bool result = IEPhysicEdgeCollision::CC_Collide(a_edge_info->m_radius, b_edge_info->m_radius, bPosition - aPosition, a->GetDisplacement() - b->GetDisplacement(), m_cacheN, m_cacheT);

	if (result == true)
	{
		if (m_cacheT <= 0.00000f)
		{
			return __collision_boom__;
		}
		else
		{
			return __collision_warning__;
		}
	}
	else
	{
		return __collision_safe__;
	}
}

IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonCircle(IEPhysicNode * a, IEPhysicNode * b)
{
	IEPhysicPolygon * a_edge = (IEPhysicPolygon *)(a->GetPhysicEdge());
	IEPhysicCircle * b_edge = (IEPhysicCircle *)(b->GetPhysicEdge());
	IEPhysicPolygonInfo * a_edge_info = (IEPhysicPolygonInfo *)(a_edge->GetPhysicEdgeInfo());
	IEPhysicCircleInfo * b_edge_info = (IEPhysicCircleInfo *)(b_edge->GetPhysicEdgeInfo());

	IEVector aPosition = a->m_position;
	IEVector bPosition = b->m_position + IEVector(b_edge->GetOffsetPosition()[0], b_edge->GetOffsetPosition()[1]);

	m_cacheT = 1.0f;
	m_cacheN = IEVector(0.0f, 0.0f);
	bool result = IEPhysicEdgeCollision::PC_Collide(a_edge_info->m_vertexs, a_edge_info->m_vertexsCount, b_edge_info->m_radius, bPosition - aPosition, a->GetDisplacement() - b->GetDisplacement(), m_cacheN, m_cacheT);

	if (result == true)
	{
		if (m_cacheT <= 0.00000f)
		{
			return __collision_boom__;
		}
		else
		{
			return __collision_warning__;
		}
	}
	else
	{
		return __collision_safe__;
	}
}

IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonDot(IEPhysicNode * a, IEPhysicNode * b)
{
	return __collision_safe__;
}

bool IEPhysicEdgeCollision::CC_Collide(const float a_radius, const float b_radius, const IEVector &offset, const IEVector &vel, IEVector &N, float &t)
{
	N = -offset;
	N.Normalize();
	t = 0.0f;

	float dis = offset.Length();
	if ((a_radius + b_radius) > dis)
	{
		float reboundLength = a_radius + b_radius - dis;
		t = -reboundLength * N.Length();
		return true;
	}
	else
	{
		IEVector oppositeVel = -vel;
		if (oppositeVel * offset <= 0)
		{
			//相反方向的速度
			t = -1.0f;
			return false;
		}

		IEVector xAxis = IEVector(-vel.m_y, vel.m_x);
		float offsetLength = xAxis * offset / (xAxis.Length());
		offsetLength = __IE_ABS__(offsetLength);
		if (offsetLength > (a_radius + b_radius))
		{
			//两者当前不想交，且未来也不会相交 介于平行和擦肩而过之间
			return false;
		}
		else
		{
			//两者可能相交 计算相交时间
			double t1 = atan2(offset.m_y, offset.m_x);
			double t2 = atan2(-vel.m_y, -vel.m_x);
			double t3 = t1 - t2;
			t3 = t3 > 0 ? t3 : -t3;

			double tri = offset.Length() / ((a_radius + b_radius) / sin(t3));
			tri = asin(tri);
			double intersection = tri - t3;
			double len = (offset.Length()) * (offset.Length()) + (a_radius + b_radius)*(a_radius + b_radius) - 2 * (offset.Length()*(a_radius + b_radius))*cos(intersection);
			len = sqrt(len);
			float finalTime = len / (vel.Length());
			if (finalTime<0 || finalTime>t)
			{
				return false;
			}

			t = finalTime;
			return true;
		}
	}
	return false;
}

bool IEPhysicEdgeCollision::PC_Collide(const IEVector * A, int Anum, const float b_radius, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t)
{
	IEVector xAxis[64];
	float taxis[64];
	int iNumAxes = 0;

	xAxis[iNumAxes] = IEVector(-xVel.m_y, xVel.m_x);
	float fVel2 = xVel * xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);
		GetCircleInterval(b_radius, xAxis[iNumAxes], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		xAxis[iNumAxes] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);
		GetCircleInterval(b_radius, xAxis[iNumAxes], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	for (int i = 0; i < Anum; i++)
	{
		IEVector E0 = xOffset;
		IEVector E1 = A[i];
		IEVector E = E0 - E1;
		xAxis[iNumAxes] = E;

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);
		GetCircleInterval(b_radius, xAxis[iNumAxes], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	if (!FindMTD(xAxis, taxis, iNumAxes, N, t))
	{
		return false;
	}

	if (N * xOffset < 0.0f)
	{
		N = -N;
	}

	return true;
}

bool IEPhysicEdgeCollision::PD_Collide(const IEVector * A, int Anum, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t)
{
	IEVector xAxis[64];
	float taxis[64];
	int iNumAxes = 0;

	xAxis[iNumAxes] = IEVector(-xVel.m_y, xVel.m_x);
	float fVel2 = xVel * xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		xAxis[iNumAxes] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	if (!FindMTD(xAxis, taxis, iNumAxes, N, t))
	{
		return false;
	}

	if (N * xOffset < 0.0f)
	{
		N = -N;
	}

	return true;
}

bool IEPhysicEdgeCollision::PP_Collide(const IEVector * A, int Anum, const IEVector * B, int Bnum, const IEVector &xOffset, const IEVector &xVel, IEVector &N, float &t)
{
	IEVector xAxis[64];
	float taxis[64];
	int iNumAxes = 0;

	xAxis[iNumAxes] = IEVector(-xVel.m_y, xVel.m_x);
	float fVel2 = xVel * xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);
		GetPolygonInterval(B, Bnum, xAxis[iNumAxes], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		xAxis[iNumAxes] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, xAxis[iNumAxes], min0, max0);
		GetPolygonInterval(B, Bnum, xAxis[iNumAxes], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, xAxis[iNumAxes], xOffset, xVel, taxis[iNumAxes], t))
		{
			return false;
		}
		iNumAxes++;
	}

	if (!FindMTD(xAxis, taxis, iNumAxes, N, t))
	{
		return false;
	}

	if (N * xOffset < 0.0f)
	{
		N = -N;
	}

	return true;
}

bool IEPhysicEdgeCollision::IntervalIntersect(float min0, float max0, float min1, float max1, const IEVector &xAxis, const IEVector &xOffset, const IEVector &xVel, float &taxis, float tmax)
{
	float h = xOffset * xAxis;
	max1 += h;
	min1 += h;

	float d0 = min0 - max1;
	float d1 = min1 - max0;

	if (d0 > 0.0f || d1 > 0.0f)
	{
		float v = xVel * xAxis;

		if (fabs(v) < 0.0000001f)
		{
			return false;
		}

		float t0 = -d0 / v;
		float t1 = d1 / v;

		if (t0 > t1)
		{
			float temp = t0;
			t0 = t1;
			t1 = temp;
		}
		taxis = (t0 > 0.0f) ? t0 : t1;

		if (taxis < 0.0f || taxis > tmax)
		{
			return false;
		}
		return true;
	}
	else
	{
		taxis = (d0 > d1) ? d0 : d1;
		return true;
	}
}

void IEPhysicEdgeCollision::GetPolygonInterval(const IEVector * axVertices, int iNumVertices, const IEVector &xAxis, float &min, float &max)
{
	min = max = (axVertices[0] * xAxis);
	for (int i = 1; i < iNumVertices; i++)
	{
		float d = (axVertices[i] * xAxis);
		if (d < min)
		{
			min = d;
		}
		else if (d > max)
		{
			max = d;
		}
	}
}

void IEPhysicEdgeCollision::GetCircleInterval(float radius, const IEVector &xAxis, float &min, float &max)
{
	float val = sqrt(xAxis * xAxis) * radius;
	if (val >= 0)
	{
		max = val;
		min = -val;
	}
	else
	{
		max = -val;
		min = val;
	}
}

bool IEPhysicEdgeCollision::FindMTD(IEVector * xAxis, float * taxis, int iNumAxes, IEVector &N, float &t)
{
	int mini = -1;
	t = 0.0f;
	for (int i = 0; i < iNumAxes; i++)
	{
		if (taxis[i] > 0)
		{
			if (taxis[i] > t)
			{
				mini = i;
				t = taxis[i];
				N = xAxis[i];
				N.Normalize();
			}
		}
	}

	if (mini != -1)
	{
		return true;
	}
	mini = -1;
	for (int i = 0; i < iNumAxes; i++)
	{
		float n = xAxis[i].Length();
		xAxis[i].Normalize();
		taxis[i] /= n;

		if (taxis[i] > t || mini == -1)
		{
			mini = i;
			t = taxis[i];
			N = xAxis[i];
		}
	}

	if (mini == -1)
	{
		printf("Error\n");
	}

	return (mini != -1);
}

IE_END