#define __IE_DLL_EXPORTS__
#include "IETerrainList.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"
#include "../../../tools/IEtime.h"

IE_BEGIN

IETerrainList * IETerrainList::m_staticTerrainsManager = NULL;

IETerrainList::IETerrainList()
{
	m_entrys = NULL;
	m_entrysCount = 0;
}

IETerrainList::~IETerrainList()
{
	if (m_entrys)
	{
		delete[] m_entrys;
	}
}

void IETerrainList::Initialization()
{
	LoadList();
}

void IETerrainList::Release()
{
	delete this;
}

IETerrainList * IETerrainList::Share()
{
	if (m_staticTerrainsManager == NULL)
	{
		m_staticTerrainsManager = new IETerrainList();
		m_staticTerrainsManager->Initialization();
	}
	return m_staticTerrainsManager;
}

void IETerrainList::LoadList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["terrainInfoFile"]);
	__IE_NEW_UNEXIST_FILE__(fileDir.GetString());

	FILE * fp = fopen(fileDir.GetString(), "r");
	if (!fp)
	{
		__IE_ERROR__("IETerrainList : can not read terrain file.\n");
		return;
	}

	fscanf(fp, "%ud", &m_entrysCount);
	m_entrysCount = m_entrysCount > 0 ? m_entrysCount : 1;
	m_entrys = new IETerrainEntry[m_entrysCount];

	unsigned int index = 0;
	IETerrainEntry info;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &info._TerrainID, info._TerrainName);

		if (info._TerrainID)
		{
			fileDir = IEString(info._TerrainName) << ".xml";

			info._LuaScript = NULL;
			info._Xml = IEXml::Create(fileDir.GetString());

			memcpy(&(m_entrys[info._TerrainID]), &info, sizeof(IETerrainEntry));
		}

		info._LuaScript = NULL;
		info._Xml = NULL;
	}
	
	fclose(fp);
}

void IETerrainList::SaveList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["terrainInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "w");

	if (!fp)
	{
		__IE_ERROR__("IETerrainList : can not read terrain file.\n");
		return;
	}

	fprintf(fp, "%d", m_entrysCount);

	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._TerrainID)
		{
			fprintf(fp, "\n%d %s", m_entrys[index]._TerrainID, m_entrys[index]._TerrainName);
		}
		else
		{
			fprintf(fp, "\n0 null");
		}
	}

	fclose(fp);
}

IETerrainEntry * IETerrainList::GetEntrys()
{
	return m_entrys;
}

unsigned int IETerrainList::GetEntrysCount()
{
	return m_entrysCount;
}

void IETerrainList::AddEntry(const char * terrainName)
{
	//首先检测是否已经有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._TerrainName, terrainName) == 0)
		{
			return;
		}
	}

	//对于新加入的资源文件，自动给予一个新的id
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._TerrainID == 0)
		{
			m_entrys[index]._TerrainID = index;
			strcpy(m_entrys[index]._TerrainName, terrainName);

			return;
		}
	}

	//说明没有空间了 扩充空间
	unsigned int emptyIndex = m_entrysCount;
	m_entrysCount = m_entrysCount * 2;

	IETerrainEntry * newEntrys = new IETerrainEntry[m_entrysCount];
	memcpy(newEntrys, m_entrys, sizeof(IETerrainEntry)* emptyIndex);
	delete[] m_entrys;
	m_entrys = newEntrys;

	m_entrys[emptyIndex]._TerrainID = emptyIndex;
	strcpy(m_entrys[emptyIndex]._TerrainName, terrainName);

	//最后保存修改
	SaveList();
}

void IETerrainList::DelEntry(const char * terrainName)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._TerrainName, terrainName) == 0)
		{
			m_entrys[index]._TerrainID = 0;
		}
	}

	SaveList();
}

void IETerrainList::DelEntry(unsigned int terrainID)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._TerrainID == terrainID)
		{
			m_entrys[index]._TerrainID = 0;
		}
	}

	SaveList();
}

IE_END