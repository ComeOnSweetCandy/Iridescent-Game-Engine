#define __IE_DLL_EXPORTS__
#include "IEtriggerManager.h"

#include "../../core/container/IEcontianer.h"

IE_BEGIN

IETriggerManager::IETriggerManager()
{
	m_triggers = NULL;
}

IETriggerManager::~IETriggerManager()
{
	if (m_triggers)
	{
		m_triggers->Release();
		m_triggers = NULL;
	}
}

void IETriggerManager::Initialization()
{
	m_triggers = IEContainer::CreateAndRetain();
}

IETriggerManager * IETriggerManager::Create()
{
	IETriggerManager * m_triggerManager = new IETriggerManager();
	m_triggerManager->Initialization();
	return m_triggerManager;
}

void IETriggerManager::Run()
{
	IETrigger ** triggers = (IETrigger **)(m_triggers->GetContainer());
	int triggersCount = m_triggers->Count();

	for (int index = 0; index < triggersCount; index++)
	{
		IETrigger * trigger = triggers[index];
		bool isEnd = trigger->GetClockEnd();
		if (isEnd)
		{
			trigger->ClockTick();
			m_triggers->Delete(index);
		}
		else
		{
			trigger->RunTrigger();
		}
	}
 	m_triggers->CleanSpace();
}

void IETriggerManager::AddTrigger(IETrigger * trigger)
{
	m_triggers->Push(trigger);
}

IE_END