#define __IE_DLL_EXPORTS__
#include "IEThingList.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"

IE_BEGIN

IEAdorningsInfoManager * IEAdorningsInfoManager::m_staticAdorningsManager = NULL;

IEAdorningsInfoManager::IEAdorningsInfoManager()
{
	m_entrysCount = 0;
}

IEAdorningsInfoManager::~IEAdorningsInfoManager()
{
	if (m_entrys)
	{
		for (unsigned int index = 0; index < m_entrysCount; index++)
		{
			if (m_entrys[index]._OccupyInfo)
			{
				delete[] m_entrys[index]._OccupyInfo;
			}
			m_entrys[index]._OccupyInfo = NULL;
		}
		delete[] m_entrys;
		m_entrys = NULL;
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
	//IEString * baseDir = (IEString *)SETTING["basedir"];
	//IEString fileDir = *baseDir + "adorning";

	//FILE * filePoint = fopen(fileDir.GetString(), "rb");
	//fread(&m_entrysCount, sizeof(unsigned int), 1, filePoint);
	//if (m_entrysCount == 0)
	//{
	//	return;
	//}

	//m_entrys = new IEThingEntry[m_entrysCount];

	//for (unsigned int index = 0; index < m_entrysCount; index++)
	//{
	//	fread(&m_entrys[index], sizeof(IEThingEntry) - sizeof(int) * 2, 1, filePoint);
	//	m_entrys[index]._OccupyInfo = new IEAdorningOccupyInfo[m_entrys[index]._OccupyCount];
	//	m_entrys[index]._LuaScript = NULL;
	//	m_entrys[index]._XML = IEXml::Create(fileDir.GetString());

	//	printf("%d  %s\n", index, m_entrys[index]._ThingName);

	//	if (m_entrys[index]._OccupyCount)
	//	{
	//		fread(m_entrys[index]._OccupyInfo, sizeof(IEAdorningOccupyInfo), m_entrys[index]._OccupyCount, filePoint);
	//	}
	//}

	//fclose(filePoint);

	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["thingInfoFile"]);
	__IE_NEW_UNEXIST_FILE__(fileDir.GetString());

	FILE * fp = fopen(fileDir.GetString(), "r");
	if (!fp)
	{
		__IE_ERROR__("IEThingList : can not read terrain file.\n");
		return;
	}

	fscanf(fp, "%ud", &m_entrysCount);
	m_entrysCount = m_entrysCount > 0 ? m_entrysCount : 1;
	m_entrys = new IEThingEntry[m_entrysCount];

	unsigned int index = 0;
	IEThingEntry info;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &info._ThingID, info._ThingName);

		if (info._ThingID)
		{
			fileDir = IEString(info._ThingName) << ".xml";

			info._LuaScript = NULL;
			info._XML = IEXml::Create(fileDir.GetString());

			//Î±Ôì²ÎÊý
			info._OccupyCount = 0;
			info._OccupyInfo = NULL;

			memcpy(&(m_entrys[info._ThingID]), &info, sizeof(IEThingEntry));
		}

		info._LuaScript = NULL;
		info._XML = NULL;
	}

	fclose(fp);
}

void IEAdorningsInfoManager::SaveAdorningsInfo()
{
	FILE * filePoint = fopen("../Debug/data/adorning", "wb");
	fwrite(&m_entrysCount, sizeof(unsigned int), 1, filePoint);
	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		fwrite(&m_entrys[index], sizeof(IEThingEntry)-sizeof(int), 1, filePoint);

		if (m_entrys[index]._OccupyCount)
		{
			fwrite(m_entrys[index]._OccupyInfo, sizeof(IEAdorningOccupyInfo), m_entrys[index]._OccupyCount, filePoint);
		}
	}
	fclose(filePoint);
}

IEThingEntry * IEAdorningsInfoManager::GetAdorningsInfoList()
{
	return m_entrys;
}

unsigned int IEAdorningsInfoManager::GetAdorningsInfoCount()
{
	return m_entrysCount;
}

IE_END