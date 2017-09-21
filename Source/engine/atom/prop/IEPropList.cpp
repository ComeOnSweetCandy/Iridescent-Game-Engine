#define __IE_DLL_EXPORTS__
#include "IEPropList.h"

#include "../../../core/container/IEdictionary.h"
#include "../../../type/IEstring.h"

IE_BEGIN

IEPropList * IEPropList::m_staticList = NULL;

IEPropList::IEPropList()
{
	m_entrysCount = 0;
}

IEPropList::~IEPropList()
{
	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		__IE_RELEASE_DIF__(m_entrys[index]._XML);
		__IE_LUA_RELEASE__(m_entrys[index]._LUA);
	}
	if (m_entrys)
	{
		delete[] m_entrys;
		m_entrys = NULL;
	}
}

void IEPropList::Initialization()
{
	IEPropList::LoadList();
}

void IEPropList::Release()
{
	delete this;
}

IEPropList * IEPropList::Share()
{
	if (m_staticList == NULL)
	{
		m_staticList = new IEPropList();
		m_staticList->Initialization();
	}
	return m_staticList;
}

IEPropEntry * IEPropList::GetEntrys()
{
	return m_entrys;
}

unsigned int IEPropList::GetEntrysCount()
{
	return m_entrysCount;
}

void IEPropList::AddEntry(const char * propName)
{
	//首先检测是否已经有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._PropName, propName) == 0)
		{
			return;
		}
	}

	//对于新加入的资源文件，自动给予一个新的id
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._PropID == 0)
		{
			m_entrys[index]._PropID = index;
			strcpy(m_entrys[index]._PropName, propName);

			return;
		}
	}

	//说明没有空间了 扩充空间
	unsigned int emptyIndex = m_entrysCount;
	m_entrysCount = m_entrysCount * 2;

	IEPropEntry * newEntrys = new IEPropEntry[m_entrysCount];
	memcpy(newEntrys, m_entrys, sizeof(IEPropEntry)* emptyIndex);
	delete[] m_entrys;
	m_entrys = newEntrys;

	m_entrys[emptyIndex]._PropID = emptyIndex;
	strcpy(m_entrys[emptyIndex]._PropName, propName);

	//最后保存修改
	SaveList();
}

void IEPropList::DelEntry(const char * propName)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._PropName, propName) == 0)
		{
			m_entrys[index]._PropID = 0;
		}
	}

	SaveList();
}

void IEPropList::DelEntry(unsigned int propID)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._PropID == propID)
		{
			m_entrys[index]._PropID = 0;
		}
	}

	SaveList();
}

void IEPropList::LoadList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["propInfoFile"]);
	IEIsexistFile(fileDir.GetString());

	FILE * fp = fopen(fileDir.GetString(), "r");
	if (!fp)
	{
		__IE_ERROR__("IEPropList : can not read terrain file.\n");
		return;
	}

	fscanf(fp, "%ud", &m_entrysCount);
	m_entrysCount = m_entrysCount > 0 ? m_entrysCount : 1;
	m_entrys = new IEPropEntry[m_entrysCount];

	unsigned int index = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &(m_entrys[index]._PropID), m_entrys[index]._PropName);

		if (m_entrys[index]._PropID)
		{
			fileDir = IEString(m_entrys[index]._PropName) << ".xml";

			m_entrys[index]._LUA = NULL;
			m_entrys[index]._XML = IEXml::Create(fileDir.GetString());
		}
		else
		{
			m_entrys[index]._LUA = NULL;
			m_entrys[index]._XML = NULL;
		}

		index++;
	}

	fclose(fp);
}

void IEPropList::SaveList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["propInfoFile"]);
	FILE * filePoint = fopen(fileDir.GetString(), "wb");
	fwrite(&m_entrysCount, sizeof(unsigned int), 1, filePoint);
	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		fwrite(&m_entrys[index], 8, 1, filePoint);
	}
	fclose(filePoint);
}

IE_END