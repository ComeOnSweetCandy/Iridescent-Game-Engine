/***********************************
* name     : IEBlock
* creater  : cosc
* info     : block
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_BLOCK__
#define __IE_BLOCK__

#include "../atom/IEstill.h"

IE_BEGIN

class __IE_DLL__ IEBlock :public IEStill
{
public:
	IEBlock();
	virtual ~IEBlock();
	virtual void Initialization();
	static IEBlock * Create();
	
public:
	virtual void SetTranslate(float x, float y);	//���ظú��� �����ڽ���λ�ö�λʱ ȷ��physicNode��λ��

	void SetOrder(unsigned int order);
	unsigned int GetOrder();

protected:
	unsigned int m_order;							//���������˳�� ��terrain��thing�л������� ���ж���1��ʼ 0��Ϊ����λ
};

IE_END

#endif