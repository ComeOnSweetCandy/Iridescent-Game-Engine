#define __IE_DLL_EXPORTS__
#include "IEelement.h"

#include "../../type/IEbaseType.h"

IE_BEGIN

IEElement::IEElement()
{
	m_unitPixels = 32;
	m_regularization = false;
}

IEElement::~IEElement()
{

}

void IEElement::Initialization()
{

}

IEElement * IEElement::Create()
{
	IEElement * object = new IEElement();
	object->Initialization();
	return object;
}

void IEElement::DrawNode()
{

}

void IEElement::ChangeModelMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//为防止贴图抖动 位置归整化
	//仅限摄像机 动态物体需要归整化
	if (m_regularization)
	{
		float pixelLength = ((IEBaseType<float> *)SETTING["PixelLength"])->GetData();
		int multiple_x = (int)(m_translate[0] / pixelLength);
		int multiple_y = (int)(m_translate[1] / pixelLength);
		float recalPosition_x = multiple_x * pixelLength;
		float recalPosition_y = multiple_y * pixelLength;

		glTranslatef(recalPosition_x, recalPosition_y, 0);
	}
	else
	{
		glTranslatef(m_translate[0], m_translate[1], 0);
	}

	glRotatef(m_rotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(-m_size[0] * m_scale * m_anchor[0], -m_size[1] * m_scale * m_anchor[1], 0.0f);
	glScalef(m_scale, m_scale, 1.0f);
}

void IEElement::RevertModelMatrix()
{
	glPopMatrix();
}

void IEElement::SetUnitPiexls(int unitPiexls)
{
	m_unitPixels = unitPiexls;

	ReckonSize();
}

void IEElement::SetRegularization(bool regularization)
{
	m_regularization = regularization;
}

void IEElement::ReckonSize()
{

}

IE_END