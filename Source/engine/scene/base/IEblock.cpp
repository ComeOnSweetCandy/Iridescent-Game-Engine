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
		//存储当前计算出来的位置值
		float physicPosition[2] = { m_translate[0], m_translate[1] };

		//追溯父节点的位置
		IENode * node = this;
		while (node = node->GetParentNode())
		{
			const float * translate = node->GetTranslate();
			physicPosition[0] += translate[0];
			physicPosition[1] += translate[1];
		}

		//如果是圆形的物理轮廓 那么需要置中
		if (m_physicNode->GetPhysicEdge()->GetEdgeType() == __edge_circle__)
		{
			const float * size = GetSize();
			physicPosition[0] += size[0];
			physicPosition[1] += size[1];
		}

		//设定绑定的physicNode的位置
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