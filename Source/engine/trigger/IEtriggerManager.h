/***********************************
* name     : IEtriggerManager.h
* creater  : cosc
* info     : trigger base class
* c_date   : 2017/1/19
* l_date   : 2017/1/19
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TRIGGER_MANAGER__
#define __IE_TRIGGER_MANAGER__

#include "IEcollisionTrigger.h"
#include "IEinteractionTrigger.h"

IE_BEGIN

class IEContainer;

class __IE_DLL__ IETriggerManager:public IEObject
{
public:
	IETriggerManager();
	virtual ~IETriggerManager();
	virtual void Initialization();
	static IETriggerManager * Create();

public:
	virtual void Run();
	void AddTrigger(IETrigger * trigger);
	void DelTrigger(IETrigger * trigger);

private:
	IEContainer * m_triggers;
};

IE_END

#endif