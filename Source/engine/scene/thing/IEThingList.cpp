#define __IE_DLL_EXPORTS__
#include "IEThingList.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"

IE_BEGIN

IEThingList * IEThingList::m_stackList = NULL;

IEThingList::IEThingList()
{
	m_entrysCount = 0;
}

IEThingList::~IEThingList()
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

void IEThingList::Initialization()
{
	IEThingList::LoadList();
}

void IEThingList::Release()
{
	delete this;
}

IEThingList * IEThingList::Share()
{
	if (m_stackList == NULL)
	{
		m_stackList = new IEThingList();
		m_stackList->Initialization();
	}
	return m_stackList;
}

IEThingEntry * IEThingList::GetEntrys()
{
	return m_entrys;
}

unsigned int IEThingList::GetEntrysCount()
{
	return m_entrysCount;
}

void IEThingList::AddEntry(const char * thingName)
{
	//首先检测是否已经有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._ThingName, thingName) == 0)
		{
			return;
		}
	}

	//对于新加入的资源文件，自动给予一个新的id
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._ThingID == 0)
		{
			m_entrys[index]._ThingID = index;
			strcpy(m_entrys[index]._ThingName, thingName);

			return;
		}
	}

	//说明没有空间了 扩充空间
	unsigned int emptyIndex = m_entrysCount;
	m_entrysCount = m_entrysCount * 2;

	IEThingEntry * newEntrys = new IEThingEntry[m_entrysCount];
	memcpy(newEntrys, m_entrys, sizeof(IEThingEntry)* emptyIndex);
	delete[] m_entrys;
	m_entrys = newEntrys;

	m_entrys[emptyIndex]._ThingID = emptyIndex;
	strcpy(m_entrys[emptyIndex]._ThingName, thingName);

	//最后保存修改
	SaveList();
}

void IEThingList::DelEntry(const char * thingName)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._ThingName, thingName) == 0)
		{
			m_entrys[index]._ThingID = 0;
		}
	}

	SaveList();
}

void IEThingList::DelEntry(unsigned int tingID)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._ThingID == tingID)
		{
			m_entrys[index]._ThingID = 0;
		}
	}

	SaveList();
}

void IEThingList::LoadList()
{
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

			info._LUA = NULL;
			info._XML = IEXml::Create(fileDir.GetString());

			//伪造参数
			info._OccupyCount = 0;
			info._OccupyInfo = NULL;

			memcpy(&(m_entrys[info._ThingID]), &info, sizeof(IEThingEntry));
		}

		info._LUA = NULL;
		info._XML = NULL;
	}

	fclose(fp);
}

void IEThingList::SaveList()
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

IE_END