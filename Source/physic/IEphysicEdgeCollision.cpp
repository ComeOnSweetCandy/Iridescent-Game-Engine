#define __IE_DLL_EXPORTS__
#include "IEphysicEdgeCollision.h"

IE_BEGIN

IEVector IEPhysicEdgeCollision::_CacheN = IEVector(0.0f,0.0f);
float IEPhysicEdgeCollision::_CacheT = 0.0f;

IEVector IEPhysicEdgeCollision::_Axis[64];
unsigned int IEPhysicEdgeCollision::_NumAxis;
float IEPhysicEdgeCollision::_Taxis[64];

IEPhysicCollisionState IEPhysicEdgeCollision::EdgeCoincidence(IEPhysicNode * a, IEPhysicNode * b, IEVector &axis, float &t)
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

	axis = _CacheN;
	t = _CacheT;

	return result;
}

inline IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonPolygon(IEPhysicNode * nodeA, IEPhysicNode * nodeB)
{
	IEPhysicPolygon * _edgeA = (IEPhysicPolygon *)(nodeA->GetPhysicEdge());
	IEPhysicPolygon * _edgeB = (IEPhysicPolygon *)(nodeB->GetPhysicEdge());

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//计算两者当前位置之差
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//计算两者当前位移值之差
	float minA, maxA, minB, maxB;																					//接下来存储极值的

	//首先测算 位移方向的垂直线作为轴 是否会相交
	_Axis[_NumAxis] = IEVector(-_displacement.m_y, _displacement.m_x);
	float displacementLength = _displacement * _displacement;

	//是否存在位移 如果不存在位移 没有计算的需要
	if (displacementLength > 0.00001f)
	{
		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetPolygonInterval(_edgeB->m_vertexs, _edgeB->m_vertexsNum, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			//首先判定方向轴 为什么判定方向的横轴 因为这能够直接告诉两者未来时间会不会相交 A是否是朝着B的方向去的 如果在此计算为false 那么后面也就没有判定未来相交的必要性了
			//如果为正值 或者在规定位移距离 或者时间内返回true 那么两者必定会相交 只是时间问题
			//说明以移动方向横向作为轴 发现两者在当前和0~_CacheT的时间内都不存在相交
			return __collision_safe__;
		}
		_NumAxis++;
	}

	for (unsigned int j = _edgeA->m_vertexsNum - 1, i = 0; i < _edgeA->m_vertexsNum; j = i, i++)
	{
		IEVector E0 = _edgeA->m_vertexs[j];
		IEVector E1 = _edgeA->m_vertexs[i];
		IEVector E = E1 - E0;
		_Axis[_NumAxis] = IEVector(-E.m_y, E.m_x);

		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetPolygonInterval(_edgeB->m_vertexs, _edgeB->m_vertexsNum, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			//说明以各边的垂直线作为轴 发现两者在当前和0~_CacheT的时间内都不存在相交
			return __collision_safe__;
		}
		_NumAxis++;
	}

	//整理数据
	if (!FindMTD())
	{
		return __collision_safe__;
	}

	//这里暂且不懂什么意思
	if (_CacheN * _distance < 0.0f)
	{
		_CacheN = -_CacheN;
	}

	//返回已经相交 还是即将相交
	if (_CacheT <= 0.00000f)
	{
		return __collision_boom__;
	}
	else
	{
		return __collision_warning__;
	}
}

IEPhysicCollisionState IEPhysicEdgeCollision::CollisionCircleCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB)
{
	IEPhysicCircle * _edgeA = (IEPhysicCircle *)(nodeA->GetPhysicEdge());
	IEPhysicCircle * _edgeB = (IEPhysicCircle *)(nodeB->GetPhysicEdge());

	//IEVector aPosition = a->m_position + IEVector(a_edge->GetOffsetPosition()[0], a_edge->GetOffsetPosition()[1]);
	//IEVector bPosition = b->m_position + IEVector(b_edge->GetOffsetPosition()[0], b_edge->GetOffsetPosition()[1]);

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//计算两者当前位置之差
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//计算两者当前位移值之差

	float radiusA = _edgeA->m_radius;		//A的半径
	float radiusB = _edgeB->m_radius;		//B的半径

	_CacheN = -_distance;					//两者间的距离方向作为弹出方向
	_CacheN.Normalize();

	float distanceLength = _distance.Length();
	if ((radiusA + radiusB) > distanceLength)
	{
		//如果两者相交
		float reboundLength = radiusA + radiusB - distanceLength;
		_CacheT = -reboundLength * _CacheN.Length();

		return __collision_boom__;
	}
	else
	{
		IEVector oppositeDisplacement = -_displacement;
		if (oppositeDisplacement * _distance <= 0)
		{
			//相反方向的速度
			_CacheT = -1.0f;
			return __collision_safe__;
		}

		IEVector axis = IEVector(-_displacement.m_y, _displacement.m_x);
		float offsetLength = axis * _distance / (axis.Length());
		offsetLength = __IE_ABS__(offsetLength);
		if (offsetLength > (radiusA + radiusB))
		{
			//两者当前不想交，且未来也不会相交 介于平行和擦肩而过之间
			return __collision_safe__;
		}
		else
		{
			//两者可能相交 计算相交时间
			double t1 = atan2(_distance.m_y, _distance.m_x);
			double t2 = atan2(-_displacement.m_y, -_displacement.m_x);
			double t3 = t1 - t2;
			t3 = t3 > 0 ? t3 : -t3;

			double tri = _distance.Length() / ((radiusA + radiusB) / sin(t3));
			tri = asin(tri);
			double intersection = tri - t3;
			double len = (_distance.Length()) * (_distance.Length()) + (radiusA + radiusB)*(radiusA + radiusB) - 2 * (_distance.Length()*(radiusA + radiusB))*cos(intersection);
			len = sqrt(len);
			float finalTime = len / (_displacement.Length());
			if (finalTime<0 || finalTime>_CacheT)
			{
				//如若两者相反方向 或者消耗的时间大于_CacheT
				return __collision_safe__;
			}

			_CacheT = finalTime;
			return __collision_warning__;
		}
	}
}

IEPhysicCollisionState IEPhysicEdgeCollision::CollisionPolygonCircle(IEPhysicNode * nodeA, IEPhysicNode * nodeB)
{
	IEPhysicPolygon * _edgeA = (IEPhysicPolygon *)(nodeA->GetPhysicEdge());
	IEPhysicCircle * _edgeB = (IEPhysicCircle *)(nodeB->GetPhysicEdge());

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//计算两者当前位置之差
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//计算两者当前位移值之差
	float minA, maxA, minB, maxB;																					//接下来存储极值的

	//首先测算 位移方向的垂直线作为轴 是否会相交
	_Axis[_NumAxis] = IEVector(-_displacement.m_y, _displacement.m_x);
	float displacementLength = _displacement * _displacement;

	if (displacementLength > 0.00001f)
	{
		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetCircleInterval(_edgeB->m_radius, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			return __collision_safe__;
		}
		_NumAxis++;
	}

	for (unsigned int j = _edgeA->m_vertexsNum - 1, i = 0; i < _edgeA->m_vertexsNum; j = i, i++)
	{
		IEVector E0 = _edgeA->m_vertexs[j];
		IEVector E1 = _edgeA->m_vertexs[i];
		IEVector E = E1 - E0;
		_Axis[_NumAxis] = IEVector(-E.m_y, E.m_x);

		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetCircleInterval(_edgeB->m_radius, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			return __collision_safe__;
		}
		_NumAxis++;
	}

	//这个是特有的一个地方 将圆心到多边形的每个顶点连成线后的垂直线作为轴线进行计算 增加精度 
	for (unsigned int i = 0; i < _edgeA->m_vertexsNum; i++)
	{
		IEVector E0 = _distance;
		IEVector E1 = _edgeA->m_vertexs[i];
		IEVector E = E0 - E1;
		_Axis[_NumAxis] = E;

		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetCircleInterval(_edgeB->m_radius, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			return __collision_safe__;
		}
		_NumAxis++;
	}

	if (!FindMTD())
	{
		return __collision_safe__;
	}

	if (_CacheN * _distance < 0.0f)
	{
		_CacheN = -_CacheN;
	}

	if (_CacheT <= 0.00000f)
	{
		return __collision_boom__;
	}
	else
	{
		return __collision_warning__;
	}
}

bool IEPhysicEdgeCollision::IntervalIntersect(float minA, float maxA, float minB, float maxB, const IEVector &axis, const IEVector &distance, const IEVector &displacement, float &taxis, float tmax)
{
	//两者之间相差的距离 在轴线上的投影的值 加到其中一个物理体上
	float h = distance * axis;
	maxB += h;
	minB += h;

	//计算两段极值的差值
	float d0 = minA - maxB;
	float d1 = minB - maxA;

	if (d0 > 0.0f || d1 > 0.0f)
	{
		//当前状态下不想交 那么需要检测 如果沿着displacement方向位移 是否有两段极值相交的可能
		float v = displacement * axis;

		//当位移距离可以忽略不计的时候 直接返回 判定为不可能相交
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
			//如果需要花费的时间为负值或者超过最大时间 那么两者不会在接下来的时间相交 当前也不相交
			return false;
		}

		//当前不相交 在未来某段时间可能在轴线上会相交 此时taxis作为时间
		return true;
	}
	else
	{
		//从此条轴线上看来 当前是相交的 并给出两极值相交段的长度 此时taxis作为长度
		taxis = (d0 > d1) ? d0 : d1;
		return true;
	}
}

void IEPhysicEdgeCollision::GetPolygonInterval(const IEVector * vertexs, unsigned int vertexsNum, const IEVector &axis, float &min, float &max)
{
	min = max = (vertexs[0] * axis);
	for (unsigned int index = 1; index < vertexsNum; index++)
	{
		float value = (vertexs[index] * axis);
		if (value < min)
		{
			min = value;
		}
		else if (value > max)
		{
			max = value;
		}
	}
}

void IEPhysicEdgeCollision::GetCircleInterval(float radius, const IEVector &axis, float &min, float &max)
{
	float val = sqrt(axis * axis) * radius;
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

bool IEPhysicEdgeCollision::FindMTD()
{
	//正常情况下 程序跑到这里 基本意味着 不是在当前相交 就是在未来相交
	//先判定在未来时间点是否相交
	int mini = -1;
	_CacheT = 0.0f;
	for (unsigned int index = 0; index < _NumAxis; index++)
	{
		//如果这个值大于0.0f 只要一个值不是小于0.0f的 就意味着当前A和B不想交 即在未来轴上相交 
		//如果所有的值都小于0.0f 那直接跳过这个循环 因为这意味着A和B相交
		if (_Taxis[index] > 0.0f)
		{
			//找到需要的最多的时间的序列
			if (_Taxis[index] > _CacheT)
			{
				mini = index;
				_CacheT = _Taxis[index];		//记录下时间
				_CacheN = _Axis[index];			//记录下向哪条轴线
				_CacheN.Normalize();			//方向标准化
			}
		}
	}

	//存在未来相交的情况 返回true
	if (mini != -1)
	{
		return true;
	}

	//当所有的_Taxis的值都小于0.0f的时候
	mini = -1;
	for (unsigned int index = 0; index < _NumAxis; index++)
	{
		float length = _Axis[index].Length();						//计算轴线的长度
		_Axis[index].Normalize();									//轴线方向标准化
		_Taxis[index] = _Taxis[index] / length;						//除以轴线的长度后 就是在轴上应该进行反弹的距离

		if (_Taxis[index] > _CacheT || mini == -1)
		{
			mini = index;
			_CacheT = _Taxis[index];								//分开所需要的距离 当然这个值暂时是负值 所以越大越好 转换为正值后 就是最小值了
			_CacheN = _Axis[index];									//如果反弹 应该沿着这个方向 可以达到最短距离分开
		}
	}

	//一般都会返回true 除非哪里出错了 返回false
	if (mini != -1)
	{
		return true;
	}
	else
	{
		__IE_ERROR__("IEPhysicEdgeCollision : function FindMTD.\n");
		return false;
	}
}

IE_END