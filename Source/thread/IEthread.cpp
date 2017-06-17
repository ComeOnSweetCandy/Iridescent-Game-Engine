#define __IE_DLL_EXPORTS__
#include "IEthread.h"

IE_BEGIN

IEThreadProtocol::IEThreadProtocol()
{

}

IEThreadProtocol::~IEThreadProtocol()
{

}

void IEThreadProtocol::Initialization()
{
	CreateThread(NULL, NULL, IEThreadProtocol::ThreadProc, (LPVOID)this, NULL, NULL);
}

IEThreadProtocol * IEThreadProtocol::Create()
{
	IEThreadProtocol * object = new IEThreadProtocol();
	object->Initialization();
	return object;
}

DWORD WINAPI IEThreadProtocol::ThreadProc(LPVOID lpParam)
{
	IEThreadProtocol * lp = (IEThreadProtocol *)lpParam;
	lp->Thread();
	return 0;
}

void IEThreadProtocol::Thread()
{
	//do something here
}

IEtoolsProtocol::IEtoolsProtocol()
{

}

IEtoolsProtocol::~IEtoolsProtocol()
{

}

IE_END