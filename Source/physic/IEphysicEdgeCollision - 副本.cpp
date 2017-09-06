#define __IE_DLL_EXPORTS__
#include "IEphysicEdgeCollision.h"

IE_BEGIN

IEVector IEPhysicEdgeCollision::_CacheN = IEVector(0.0f,0.0f);
float IEPhysicEdgeCollision::_CacheT = 0.0f;

IEPhysicCollisionState IEPhysicEdgeCollision::EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &_Axis, float &t)
{
	//所有数据初始化
	IEPhysicCollisionState result = __collision_safe__;
	_CacheN = IEVector(0.0f, 0.0f);
	_CacheT = 1.0f;
	_NumAxis = 0;

	//对刚体物理形状判定
	IEEdgeType a_type = a->GetPhysicEdge()->GetEdgeType();
	IEEdgeType b_type = b->GetPhysicEdge()->GetEdgeType();

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
	}

	_Axis = _CacheN;
	t = _CacheT;

	return result;
}

inline IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonPolygon(IEPhysicNode * a, IEPhysicNode * b)
{
	IEPhysicPolygon * a_edge = ((IEPhysicPolygon *)(a->GetPhysicEdge()));
	IEPhysicPolygon * b_edge = ((IEPhysicPolygon *)(b->GetPhysicEdge()));


	bool result = IEPhysicEdgeCollision::PP_Collide(a_edge_info->m_vertexs, a_edge_info->m_vertexsCount, b_edge_info->m_vertexs, b_edge_info->m_vertexsCount, \
													b->m_position - a->m_position, a->GetDisplacement() - b->GetDisplacement(), _CacheN, _CacheT);
	
	IEVector _xVel = b->m_position - a->m_position;

	//主体计算部分
	_Axis[_NumAxis] = IEVector(-_xVel.m_y, _xVel.m_x);
	float fVel2 = _xVel * _xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetPolygonInterval(B, Bnum, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, _xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		_Axis[_NumAxis] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetPolygonInterval(B, Bnum, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, _xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	if (!FindMTD(_Axis, _Taxis, _NumAxis, N, t))
	{
		return false;
	}

	if (N * xOffset < 0.0f)
	{
		N = -N;
	}

	return true;


	if (result == true)
	{
		if (_CacheT <= 0.00000f)
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

	_CacheT = 1.0f;
	bool result = IEPhysicEdgeCollision::CC_Collide(a_edge_info->m_radius, b_edge_info->m_radius, bPosition - aPosition, a->GetDisplacement() - b->GetDisplacement(), _CacheN, _CacheT);

	if (result == true)
	{
		if (_CacheT <= 0.00000f)
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

	_CacheT = 1.0f;
	_CacheN = IEVector(0.0f, 0.0f);
	bool result = IEPhysicEdgeCollision::PC_Collide(a_edge_info->m_vertexs, a_edge_info->m_vertexsCount, b_edge_info->m_radius, bPosition - aPosition, a->GetDisplacement() - b->GetDisplacement(), _CacheN, _CacheT);

	if (result == true)
	{
		if (_CacheT <= 0.00000f)
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

		IEVector _Axis = IEVector(-vel.m_y, vel.m_x);
		float offsetLength = _Axis * offset / (_Axis.Length());
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
	
	
	

	_Axis[_NumAxis] = IEVector(-xVel.m_y, xVel.m_x);
	float fVel2 = xVel * xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetCircleInterval(b_radius, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		_Axis[_NumAxis] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetCircleInterval(b_radius, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	for (int i = 0; i < Anum; i++)
	{
		IEVector E0 = xOffset;
		IEVector E1 = A[i];
		IEVector E = E0 - E1;
		_Axis[_NumAxis] = E;

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetCircleInterval(b_radius, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	if (!FindMTD(_Axis, _Taxis, _NumAxis, N, t))
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
	
	
	

	_Axis[_NumAxis] = IEVector(-xVel.m_y, xVel.m_x);
	float fVel2 = xVel * xVel;

	if (fVel2 > 0.00001f)
	{
		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetPolygonInterval(B, Bnum, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	for (int j = Anum - 1, i = 0; i < Anum; j = i, i++)
	{
		IEVector E0 = A[j];
		IEVector E1 = A[i];
		IEVector E = E1 - E0;
		_Axis[_NumAxis] = IEVector(-E.m_y, E.m_x);

		float min0 = 0.0f, max0 = 0.0f, min1 = 0.0f, max1 = 0.0f;
		GetPolygonInterval(A, Anum, _Axis[_NumAxis], min0, max0);
		GetPolygonInterval(B, Bnum, _Axis[_NumAxis], min1, max1);

		if (!IntervalIntersect(min0, max0, min1, max1, _Axis[_NumAxis], xOffset, xVel, _Taxis[_NumAxis], t))
		{
			return false;
		}
		_NumAxis++;
	}

	if (!FindMTD(_Axis, _Taxis, _NumAxis, N, t))
	{
		return false;
	}

	if (N * xOffset < 0.0f)
	{
		N = -N;
	}

	return true;
}

bool IEPhysicEdgeCollision::IntervalIntersect(float min0, float max0, float min1, float max1, const IEVector &_Axis, const IEVector &xOffset, const IEVector &xVel, float &_Taxis, float tmax)
{
	float h = xOffset * _Axis;
	max1 += h;
	min1 += h;

	float d0 = min0 - max1;
	float d1 = min1 - max0;

	if (d0 > 0.0f || d1 > 0.0f)
	{
		float v = xVel * _Axis;

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
		_Taxis = (t0 > 0.0f) ? t0 : t1;

		if (_Taxis < 0.0f || _Taxis > tmax)
		{
			return false;
		}
		return true;
	}
	else
	{
		_Taxis = (d0 > d1) ? d0 : d1;
		return true;
	}
}

void IEPhysicEdgeCollision::GetPolygonInterval(const IEVector * axVertices, int iNumVertices, const IEVector &_Axis, float &min, float &max)
{
	min = max = (axVertices[0] * _Axis);
	for (int i = 1; i < iNumVertices; i++)
	{
		float d = (axVertices[i] * _Axis);
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

void IEPhysicEdgeCollision::GetCircleInterval(float radius, const IEVector &_Axis, float &min, float &max)
{
	float val = sqrt(_Axis * _Axis) * radius;
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

bool IEPhysicEdgeCollision::FindMTD(IEVector * _Axis, float * _Taxis, int _NumAxis, IEVector &N, float &t)
{
	int mini = -1;
	t = 0.0f;
	for (int i = 0; i < _NumAxis; i++)
	{
		if (_Taxis[i] > 0)
		{
			if (_Taxis[i] > t)
			{
				mini = i;
				t = _Taxis[i];
				N = _Axis[i];
				N.Normalize();
			}
		}
	}

	if (mini != -1)
	{
		return true;
	}
	mini = -1;
	for (int i = 0; i < _NumAxis; i++)
	{
		float n = _Axis[i].Length();
		_Axis[i].Normalize();
		_Taxis[i] /= n;

		if (_Taxis[i] > t || mini == -1)
		{
			mini = i;
			t = _Taxis[i];
			N = _Axis[i];
		}
	}

	if (mini == -1)
	{
		printf("Error\n");
	}

	return (mini != -1);
}

IE_END