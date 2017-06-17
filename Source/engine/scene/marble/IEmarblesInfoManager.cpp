#define __IE_DLL_EXPORTS__
#include "IEmarblesInfoManager.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"
#include "../../../tools/IEtime.h"

IE_BEGIN

IEMarblesInfoManager * IEMarblesInfoManager::m_staticBarblesManager = NULL;

IEMarblesInfoManager::IEMarblesInfoManager()
{
	m_marblesInfoList = NULL;
	m_marblesInfoCount = 0;
}

IEMarblesInfoManager::~IEMarblesInfoManager()
{
	if (m_marblesInfoList)
	{
		delete[] m_marblesInfoList;
	}
}

void IEMarblesInfoManager::Initialization()
{
	LoadMarblesInfo();
}

void IEMarblesInfoManager::Release()
{
	delete this;
}

IEMarblesInfoManager * IEMarblesInfoManager::Share()
{
	if (m_staticBarblesManager == NULL)
	{
		m_staticBarblesManager = new IEMarblesInfoManager();
		m_staticBarblesManager->Initialization();
	}
	return m_staticBarblesManager;
}

void IEMarblesInfoManager::LoadMarblesInfo()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["marbleInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	if (!fp)
	{
		__IE_ERROR__("IEMarblesInfoManager : can not read marble file.\n");
	}

	char buf[1024];
	while (fgets(buf, 1024, fp))
	{
		m_marblesInfoCount++;
	}

	if (m_marblesInfoCount == 0)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
	m_marblesInfoList = new IEMarbleInfo[m_marblesInfoCount];

	unsigned int index = 0;
	while (!feof(fp))
	{
		IEMarbleInfo &info = m_marblesInfoList[index];
		fscanf(fp, "%d %d %d %d %s", &(info._MarbleID), &(info._BodyC), &(info._BorderC), &(info._CornerC), info._MarbleName);

		index++;
	}

	fclose(fp);
}

void IEMarblesInfoManager::SaveMarblesInfo()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["marbleInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	if (!fp)
	{
		__IE_ERROR__("IEMarblesInfoManager : can not read marble file.\n");
	}

	fwrite(m_marblesInfoList, sizeof(IEMarbleInfo), m_marblesInfoCount, fp);
	fclose(fp);
}

IEMarbleInfo * IEMarblesInfoManager::GetMarblesInfoList()
{
	return m_marblesInfoList;
}

unsigned int IEMarblesInfoManager::GetMarblesInfoCount()
{
	return m_marblesInfoCount;
}

IE_END