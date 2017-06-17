#define __IE_DLL_EXPORTS__
#include "IEblock.h"

IE_BEGIN

IEBlock::IEBlock()
{
	m_order = 0;
}

IEBlock::~IEBlock()
{

}

void IEBlock::Initialization()
{
	IEStill::Initialization(NULL);
}

IEBlock * IEBlock::Create()
{
	IEBlock * object = new IEBlock();
	object->Initialization();
	return object;
}

void IEBlock::SetTranslate(float x, float y)
{
	IENode::SetTranslate(x, y);

	if (m_physicNode)
	{
		//�洢��ǰ���������λ��ֵ
		float physicPosition[2] = { m_translate[0], m_translate[1] };

		//׷�ݸ��ڵ��λ��
		IENode * node = this;
		while (node = node->GetParentNode())
		{
			const float * translate = node->GetTranslate();
			physicPosition[0] += translate[0];
			physicPosition[1] += translate[1];
		}

		//�����Բ�ε��������� ��ô��Ҫ����
		if (m_physicNode->GetPhysicEdge()->GetEdgeType() == __edge_circle__)
		{
			const float * size = GetSize();
			physicPosition[0] += size[0];
			physicPosition[1] += size[1];
		}

		//�趨�󶨵�physicNode��λ��
		m_physicNode->SetPhysicPosition(physicPosition[0], physicPosition[1]);
	}
}

void IEBlock::SetOrder(unsigned int order)
{
	m_order = order;
}

unsigned int IEBlock::GetOrder()
{
	return m_order;
}

IE_END