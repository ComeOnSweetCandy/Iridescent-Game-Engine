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