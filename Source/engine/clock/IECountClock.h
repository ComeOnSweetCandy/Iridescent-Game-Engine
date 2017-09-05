/***********************************
* name     : IECountClock.h
* creater  : cosc
* info     : ����clock
* date     : 2017/3/27
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_COUNT_CLOCK__
#define __IE_COUNT_CLOCK__

#include "IEclock.h"

IE_BEGIN

class __IE_DLL__ IECountClock :public IEClock
{
public:
	IECountClock();
	virtual ~IECountClock();
	virtual void Initialization(int topTimes);
	static IECountClock * Create(int topTimes);

public:
	virtual void Run();					//��������
	virtual void Stir();				//�������Ӳ���ȡ�κ��ж�
	virtual void Reset();				//����ʱ��Ϊ0

private:
	int m_maxCount;
	int m_curCount;
};

IE_END

#endif