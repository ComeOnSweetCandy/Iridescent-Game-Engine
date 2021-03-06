/***********************************
* name     : IEActin.h
* creater  : cosc
* info     : action base
* date     : 2017/1/13
* version  : 1.0
* remark   : 1.同一时间 只会执行一个action 2.action有两种 一种goal带来的 一种外部施加 外部施加优先权大于内部
************************************/

#ifndef __IE_ACTION__
#define __IE_ACTION__

#include "../IECreatureList.h"
#include "../../../../core/IEnode.h"

IE_BEGIN

class IECreature;
class IEActionMachine;

/*
** 哪些动作能够被哪些动作打断
*/
#define __ACTION_MASK__			0x1				//00000000 00000000 00000000 000000001

#define __ACTION_OPER__			0x0				//00000000 00000000 00000000 000000000

class __IE_DLL__ IEAction:public IEObject
{
public:
	IEAction();
	virtual ~IEAction();
	virtual void Initialization();
	static IEAction * Create();

public:
	virtual void KeyframeCallback();					//运行到关键帧时的反馈

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