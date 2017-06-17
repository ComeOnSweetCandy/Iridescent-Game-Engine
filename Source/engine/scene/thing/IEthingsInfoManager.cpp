#define __IE_DLL_EXPORTS__
#include "IEthingsInfoManager.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"

IE_BEGIN

IEAdorningsInfoManager * IEAdorningsInfoManager::m_staticAdorningsManager = NULL;

IEAdorningsInfoManager::IEAdorningsInfoManager()
{
	m_adorningsInfoCount = 0;
}

IEAdorningsInfoManager::~IEAdorningsInfoManager()
{
	if (m_adorningsInfoList)
	{
		for (unsigned int index = 0; index < m_adorningsInfoCount; index++)
		{
			if (m_adorningsInfoList[index]._OccupyInfo)
			{
				delete[] m_adorningsInfoList[index]._OccupyInfo;
			}
			m_adorningsInfoList[index]._OccupyInfo = NULL;
		}
		delete[] m_adorningsInfoList;
		m_adorningsInfoList = NULL;
	}
}

void IEAdorningsInfoManager::Initialization()
{
	LoadAdorningsInfo();
}

void IEAdorningsInfoManager::Release()
{
	delete this;
}

IEAdorningsInfoManager * IEAdorningsInfoManager::Share()
{
	if (m_staticAdorningsManager == NULL)
	{
		m_staticAdorningsManager = new IEAdorningsInfoManager();
		m_staticAdorningsManager->Initialization();
	}
	return m_staticAdorningsManager;
}

void IEAdorningsInfoManager::LoadAdorningsInfo()
{
	IEString * baseDir = (IEString *)SETTING["basedir"];
	IEString fileDir = *baseDir + "adorning";

	FILE * filePoint = fopen(fileDir.GetString(), "rb");
	fread(&m_adorningsInfoCount, sizeof(unsigned int), 1, filePoint);
	if (m_adorningsInfoCount == 0)
	{
		return;
	}

	m_adorningsInfoList = new IEAdorningInfo[m_adorningsInfoCount];

	for (unsigned int index = 0; index < m_adorningsInfoCount; index++)
	{
		fread(&m_adorningsInfoList[index], sizeof(IEAdorningInfo) - sizeof(int) * 2, 1, filePoint);
		m_adorningsInfoList[index]._OccupyInfo = new IEAdorningOccupyInfo[m_adorningsInfoList[index]._OccupyCount];
		m_adorningsInfoList[index]._LuaScript = NULL;

		if (m_adorningsInfoList[index]._OccupyCount)
		{
			fread(m_adorningsInfoList[index]._OccupyInfo, sizeof(IEAdorningOccupyInfo), m_adorningsInfoList[index]._OccupyCount, filePoint);
		}
	}

	fclose(filePoint);
}

void IEAdorningsInfoManager::SaveAdorningsInfo()
{
	FILE * filePoint = fopen("../Debug/data/adorning", "wb");
	fwrite(&m_adorningsInfoCount, sizeof(unsigned int), 1, filePoint);
	for (unsigned int index = 0; index < m_adorningsInfoCount; index++)
	{
		fwrite(&m_adorningsInfoList[index], sizeof(IEAdorningInfo)-sizeof(int), 1, filePoint);

		if (m_adorningsInfoList[index]._OccupyCount)
		{
			fwrite(m_adorningsInfoList[index]._OccupyInfo, sizeof(IEAdorningOccupyInfo), m_adorningsInfoList[index]._OccupyCount, filePoint);
		}
	}
	fclose(filePoint);
}

IEAdorningInfo * IEAdorningsInfoManager::GetAdorningsInfoList()
{
	return m_adorningsInfoList;
}

unsigned int IEAdorningsInfoManager::GetAdorningsInfoCount()
{
	return m_adorningsInfoCount;
}

IE_END