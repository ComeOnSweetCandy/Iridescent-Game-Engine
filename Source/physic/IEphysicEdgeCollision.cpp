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
	//�������ݳ�ʼ��
	IEPhysicCollisionState result = __collision_safe__;
	_CacheN = IEVector(0.0f, 0.0f);
	_CacheT = 1.0f;
	_NumAxis = 0;

	//�Ը���������״�ж�
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

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//�������ߵ�ǰλ��֮��
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//�������ߵ�ǰλ��ֵ֮��
	float minA, maxA, minB, maxB;																					//�������洢��ֵ��

	//���Ȳ��� λ�Ʒ���Ĵ�ֱ����Ϊ�� �Ƿ���ཻ
	_Axis[_NumAxis] = IEVector(-_displacement.m_y, _displacement.m_x);
	float displacementLength = _displacement * _displacement;

	//�Ƿ����λ�� ���������λ�� û�м������Ҫ
	if (displacementLength > 0.00001f)
	{
		GetPolygonInterval(_edgeA->m_vertexs, _edgeA->m_vertexsNum, _Axis[_NumAxis], minA, maxA);
		GetPolygonInterval(_edgeB->m_vertexs, _edgeB->m_vertexsNum, _Axis[_NumAxis], minB, maxB);

		if (!IntervalIntersect(minA, maxA, minB, maxB, _Axis[_NumAxis], _distance, _displacement, _Taxis[_NumAxis], _CacheT))
		{
			//�����ж������� Ϊʲô�ж�����ĺ��� ��Ϊ���ܹ�ֱ�Ӹ�������δ��ʱ��᲻���ཻ A�Ƿ��ǳ���B�ķ���ȥ�� ����ڴ˼���Ϊfalse ��ô����Ҳ��û���ж�δ���ཻ�ı�Ҫ����
			//���Ϊ��ֵ �����ڹ涨λ�ƾ��� ����ʱ���ڷ���true ��ô���߱ض����ཻ ֻ��ʱ������
			//˵�����ƶ����������Ϊ�� ���������ڵ�ǰ��0~_CacheT��ʱ���ڶ��������ཻ
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
			//˵���Ը��ߵĴ�ֱ����Ϊ�� ���������ڵ�ǰ��0~_CacheT��ʱ���ڶ��������ཻ
			return __collision_safe__;
		}
		_NumAxis++;
	}

	//��������
	if (!FindMTD())
	{
		return __collision_safe__;
	}

	//�������Ҳ���ʲô��˼
	if (_CacheN * _distance < 0.0f)
	{
		_CacheN = -_CacheN;
	}

	//�����Ѿ��ཻ ���Ǽ����ཻ
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

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//�������ߵ�ǰλ��֮��
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//�������ߵ�ǰλ��ֵ֮��

	float radiusA = _edgeA->m_radius;		//A�İ뾶
	float radiusB = _edgeB->m_radius;		//B�İ뾶

	_CacheN = -_distance;					//���߼�ľ��뷽����Ϊ��������
	_CacheN.Normalize();

	float distanceLength = _distance.Length();
	if ((radiusA + radiusB) > distanceLength)
	{
		//��������ཻ
		float reboundLength = radiusA + radiusB - distanceLength;
		_CacheT = -reboundLength * _CacheN.Length();

		return __collision_boom__;
	}
	else
	{
		IEVector oppositeDisplacement = -_displacement;
		if (oppositeDisplacement * _distance <= 0)
		{
			//�෴������ٶ�
			_CacheT = -1.0f;
			return __collision_safe__;
		}

		IEVector axis = IEVector(-_displacement.m_y, _displacement.m_x);
		float offsetLength = axis * _distance / (axis.Length());
		offsetLength = __IE_ABS__(offsetLength);
		if (offsetLength > (radiusA + radiusB))
		{
			//���ߵ�ǰ���뽻����δ��Ҳ�����ཻ ����ƽ�кͲ������֮��
			return __collision_safe__;
		}
		else
		{
			//���߿����ཻ �����ཻʱ��
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
				//���������෴���� �������ĵ�ʱ�����_CacheT
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

	IEVector _distance = (nodeB->m_position + _edgeB->m_barycenter) - (nodeA->m_position + _edgeA->m_barycenter);	//�������ߵ�ǰλ��֮��
	IEVector _displacement = nodeA->m_displacement - nodeB->m_displacement;											//�������ߵ�ǰλ��ֵ֮��
	float minA, maxA, minB, maxB;																					//�������洢��ֵ��

	//���Ȳ��� λ�Ʒ���Ĵ�ֱ����Ϊ�� �Ƿ���ཻ
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

	//��������е�һ���ط� ��Բ�ĵ�����ε�ÿ�����������ߺ�Ĵ�ֱ����Ϊ���߽��м��� ���Ӿ��� 
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
	//����֮�����ľ��� �������ϵ�ͶӰ��ֵ �ӵ�����һ����������
	float h = distance * axis;
	maxB += h;
	minB += h;

	//�������μ�ֵ�Ĳ�ֵ
	float d0 = minA - maxB;
	float d1 = minB - maxA;

	if (d0 > 0.0f || d1 > 0.0f)
	{
		//��ǰ״̬�²��뽻 ��ô��Ҫ��� �������displacement����λ�� �Ƿ������μ�ֵ�ཻ�Ŀ���
		float v = displacement * axis;

		//��λ�ƾ�����Ժ��Բ��Ƶ�ʱ�� ֱ�ӷ��� �ж�Ϊ�������ཻ
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
			//�����Ҫ���ѵ�ʱ��Ϊ��ֵ���߳������ʱ�� ��ô���߲����ڽ�������ʱ���ཻ ��ǰҲ���ཻ
			return false;
		}

		//��ǰ���ཻ ��δ��ĳ��ʱ������������ϻ��ཻ ��ʱtaxis��Ϊʱ��
		return true;
	}
	else
	{
		//�Ӵ��������Ͽ��� ��ǰ���ཻ�� ����������ֵ�ཻ�εĳ��� ��ʱtaxis��Ϊ����
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
	//��������� �����ܵ����� ������ζ�� �����ڵ�ǰ�ཻ ������δ���ཻ
	//���ж���δ��ʱ����Ƿ��ཻ
	int mini = -1;
	_CacheT = 0.0f;
	for (unsigned int index = 0; index < _NumAxis; index++)
	{
		//������ֵ����0.0f ֻҪһ��ֵ����С��0.0f�� ����ζ�ŵ�ǰA��B���뽻 ����δ�������ཻ 
		//������е�ֵ��С��0.0f ��ֱ���������ѭ�� ��Ϊ����ζ��A��B�ཻ
		if (_Taxis[index] > 0.0f)
		{
			//�ҵ���Ҫ������ʱ�������
			if (_Taxis[index] > _CacheT)
			{
				mini = index;
				_CacheT = _Taxis[index];		//��¼��ʱ��
				_CacheN = _Axis[index];			//��¼������������
				_CacheN.Normalize();			//�����׼��
			}
		}
	}

	//����δ���ཻ����� ����true
	if (mini != -1)
	{
		return true;
	}

	//�����е�_Taxis��ֵ��С��0.0f��ʱ��
	mini = -1;
	for (unsigned int index = 0; index < _NumAxis; index++)
	{
		float length = _Axis[index].Length();						//�������ߵĳ���
		_Axis[index].Normalize();									//���߷����׼��
		_Taxis[index] = _Taxis[index] / length;						//�������ߵĳ��Ⱥ� ����������Ӧ�ý��з����ľ���

		if (_Taxis[index] > _CacheT || mini == -1)
		{
			mini = index;
			_CacheT = _Taxis[index];								//�ֿ�����Ҫ�ľ��� ��Ȼ���ֵ��ʱ�Ǹ�ֵ ����Խ��Խ�� ת��Ϊ��ֵ�� ������Сֵ��
			_CacheN = _Axis[index];									//������� Ӧ������������� ���Դﵽ��̾���ֿ�
		}
	}

	//һ�㶼�᷵��true ������������� ����false
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