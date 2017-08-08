/***********************************
* name     : IEActin.h
* creater  : cosc
* info     : action base
* date     : 2017/1/13
* version  : 1.0
* remark   : 1.ͬһʱ�� ֻ��ִ��һ��action 2.action������ һ��goal������ һ���ⲿʩ�� �ⲿʩ������Ȩ�����ڲ�
************************************/

#ifndef __IE_ACTION__
#define __IE_ACTION__

#include "../IECreatureInfo.h"
#include "../../../../core/IEnode.h"

IE_BEGIN

class IECreature;
class IEActionMachine;

class __IE_DLL__ IEAction:public IEObject
{
public:
	IEAction();
	virtual ~IEAction();
	virtual void Initialization();
	static IEAction * Create();

public:
	virtual void KeyframeCallback();					//���е��ؼ�֡ʱ�ķ���

	void SetActionMachine(IEActionMachine * machine);

protected:
	virtual void Begin() = 0;
	virtual void Excute() = 0;
	virtual void End() = 0;

	IECreature * GetCreature();
	IEActionMachine * GetActionMachine();

protected:
	IEActionMachine * m_actionMachine;

	friend class IEActionMachine;
};

IE_END

#endif