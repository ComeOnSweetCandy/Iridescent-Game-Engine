/***********************************
* name     : IEClock.h
* creater  : cosc
* info     : �ؼ�Ŀ�����ڼ�����ʱ ���Է����������� �������������ڲ���Ӧ����һ��ʱ�� ����atom����
* date     : 2017/3/23
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CLOCK__
#define __IE_CLOCK__

#include "../../core/IEobject.h"

IE_BEGIN

class IEClock;
class IEAtom;

typedef void(IEAtom::*IEFunctionClockTick)(IEClock * self);			//��ʱ����ʱ���� Ӧ���ڻص������л��Դ�clock���� ����atom�������ò���ȥ�洢

enum __IE_DLL__ IEClockType
{
	__clock_none_type__,			//û�м�ʱ��
	__clock_time_type__,			//ʱ���ʱ��
	__clock_count_type__,			//ײ������������
	__clock_type_count__			//��ʱ�����ͼ���
};

class __IE_DLL__ IEClock:public IEObject
{
public:
	IEClock();
	virtual ~IEClock();
	virtual void Initialization();

public:
	virtual void Run() = 0;			//��������
	virtual void Reset() = 0;		//����
	virtual void Stir() = 0;		//��������

	IEClockType GetClockType();
	void AssembClock(IEAtom * atom, IEFunctionClockTick function);
	void ClockTick();

protected:
	bool m_ended;
	IEClockType m_clockType;
	IEAtom * m_attachAtom;
	IEFunctionClockTick m_function;
};

IE_END

#endif