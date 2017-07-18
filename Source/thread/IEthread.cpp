#define __IE_DLL_EXPORTS__
#include "IEthread.h"

#include "../core/container/IEcontianer.h"

IE_BEGIN

IEThreadProtocol * IEThreadProtocol::m_staticThread = NULL;

IEThreadProtocol::IEThreadProtocol()
{
	m_jobs = NULL;
}

IEThreadProtocol::~IEThreadProtocol()
{
	m_jobs->Release();
}

void IEThreadProtocol::Initialization()
{
	m_jobs = IEContainer::CreateAndRetain();

	CreateThread(NULL, NULL, IEThreadProtocol::ThreadProc, (LPVOID)this, NULL, NULL);
}

IEThreadProtocol * IEThreadProtocol::Create()
{
	IEThreadProtocol * object = new IEThreadProtocol();
	object->Initialization();
	return object;
}

IEThreadProtocol * IEThreadProtocol::Share()
{
	if (m_staticThread == NULL)
	{
		m_staticThread = new IEThreadProtocol();
		m_staticThread->Initialization();
	}
	return m_staticThread;
}

void IEThreadProtocol::Release()
{
	delete this;
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
	static int i = 0;
	while (1)
	{
		if (m_jobs->Count() == 0)
		{
			Sleep(1000);
		}
		else
		{
			while (m_jobs->Count())
			{
				//wglMakeCurrent();

				IEImage * iamge = (IEImage *)m_jobs->PopTop();
				glTexImage2D(GL_TEXTURE_2D, 0, iamge->m_imgComponents, iamge->m_imgWidth, iamge->m_imgHeight, 0, iamge->m_imgFormat, GL_UNSIGNED_BYTE, iamge->m_imgData);
				//if (iamge->m_imgWidth == iamge->m_imgHeight)
				//{
				//	
				//}
				//else
				//{
				//	glTexImage2D(GL_TEXTURE_2D, 0, iamge->m_imgComponents, iamge->m_imgWidth, iamge->m_imgHeight, 0, iamge->m_imgFormat, GL_UNSIGNED_BYTE, NULL);
				//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, iamge->m_imgWidth, iamge->m_imgHeight, iamge->m_imgFormat, GL_UNSIGNED_BYTE, iamge->m_imgData);
				//}
			}
		}
	}
}

void IEThreadProtocol::ThreadLoadImage(IEImage * image)
{
	m_jobs->Push(image);
}

IEtoolsProtocol::IEtoolsProtocol()
{

}

IEtoolsProtocol::~IEtoolsProtocol()
{

}

IE_END