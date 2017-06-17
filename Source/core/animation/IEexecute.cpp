#define __IE_DLL_EXPORTS__
#include "IEexecute.h"

IE_BEGIN

IEExecute::IEExecute()
{

}

IEExecute::~IEExecute()
{

}

void IEExecute::Initialization()
{

}

IEExecute * IEExecute::Create()
{
	IEExecute * object = new IEExecute();
	object->Initialization();
	return object;
}

void IEExecute::CompletedAction(IENode * node)
{
	if (!m_hasCompletedAction)
	{
		m_hasCompletedAction = true;

	}
}

void IEExecute::SetCircle()
{

}

void IEExecute::SetLoop()
{

}

bool IEExecute::Run(IENode * node)
{
	//node->AssembleDisplacement();

	return true;
}

IE_END