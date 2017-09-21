#define __IE_DLL_EXPORTS__
#include "IECreatureList.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"

IE_BEGIN

IECreatureList * IECreatureList::m_staticList = NULL;

IECreatureList::IECreatureList()
{
	m_entrysCount = 0;
}

IECreatureList::~IECreatureList()
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

void IECreatureList::Initialization()
{
	IECreatureList::LoadList();
}

void IECreatureList::Release()
{
	delete this;
}

IECreatureList * IECreatureList::Share()
{
	if (m_staticList == NULL)
	{
		m_staticList = new IECreatureList();
		m_staticList->Initialization();
	}
	return m_staticList;
}

IECreatureEntry * IECreatureList::GetEntrys()
{
	return m_entrys;
}

unsigned int IECreatureList::GetEntrysCount()
{
	return m_entrysCount;
}

void IECreatureList::AddEntry(const char * thingName)
{
	//首先检测是否已经有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._CreatureName, thingName) == 0)
		{
			return;
		}
	}

	//对于新加入的资源文件，自动给予一个新的id
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._CreatureID == 0)
		{
			m_entrys[index]._CreatureID = index;
			strcpy(m_entrys[index]._CreatureName, thingName);

			return;
		}
	}

	//说明没有空间了 扩充空间
	unsigned int emptyIndex = m_entrysCount;
	m_entrysCount = m_entrysCount * 2;

	IECreatureEntry * newEntrys = new IECreatureEntry[m_entrysCount];
	memcpy(newEntrys, m_entrys, sizeof(IECreatureEntry)* emptyIndex);
	delete[] m_entrys;
	m_entrys = newEntrys;

	m_entrys[emptyIndex]._CreatureID = emptyIndex;
	strcpy(m_entrys[emptyIndex]._CreatureName, thingName);

	//最后保存修改
	SaveList();
}

void IECreatureList::DelEntry(const char * thingName)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (strcmp(m_entrys[index]._CreatureName, thingName) == 0)
		{
			m_entrys[index]._CreatureID = 0;
		}
	}

	SaveList();
}

void IECreatureList::DelEntry(unsigned int tingID)
{
	//首先检测是否有了该资源文件
	for (unsigned int index = 1; index < m_entrysCount; index++)
	{
		if (m_entrys[index]._CreatureID == tingID)
		{
			m_entrys[index]._CreatureID = 0;
		}
	}

	SaveList();
}

void IECreatureList::LoadList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["creatureInfoFile"]);
	IEIsexistFile(fileDir.GetString());

	FILE * fp = fopen(fileDir.GetString(), "r");
	if (!fp)
	{
		__IE_ERROR__("IECreatureList : can not read terrain file.\n");
		return;
	}

	fscanf(fp, "%ud", &m_entrysCount);
	m_entrysCount = m_entrysCount > 0 ? m_entrysCount : 1;
	m_entrys = new IECreatureEntry[m_entrysCount];

	unsigned int index = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &(m_entrys[index]._CreatureID), m_entrys[index]._CreatureName);

		if (m_entrys[index]._CreatureID)
		{
			fileDir = IEString(m_entrys[index]._CreatureName) << ".xml";

			m_entrys[index]._LUA = NULL;
			m_entrys[index]._XML = IEXml::Create(fileDir.GetString());

			//填充数据
			IEXml * propertyXML = m_entrys[index]._XML->FindChild("property");

			m_entrys[index]._CreatureType = (IECreatureRace)(propertyXML->FindChild("race")->ValueInt());
			m_entrys[index]._View = propertyXML->FindChild("view")->ValueFloat();
			m_entrys[index]._BaseHealth = propertyXML->FindChild("baseHealth")->ValueInt();
			m_entrys[index]._GrowHealth = propertyXML->FindChild("growHealth")->ValueInt();
			m_entrys[index]._BaseMagic = propertyXML->FindChild("baseMagic")->ValueInt();
			m_entrys[index]._GrowMagic = propertyXML->FindChild("growMagic")->ValueInt();
			m_entrys[index]._BaseSpeed = propertyXML->FindChild("baseSpeed")->ValueInt();
			m_entrys[index]._GrowSpeed = propertyXML->FindChild("growSpeed")->ValueInt();
			m_entrys[index]._BaseDamage = propertyXML->FindChild("physicDamage")->ValueInt();
			m_entrys[index]._GrowDamage = propertyXML->FindChild("growPhysicDamage")->ValueInt();
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

void IECreatureList::SaveList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["creatureInfoFile"]);
	FILE * filePoint = fopen(fileDir.GetString(), "wb");
	fwrite(&m_entrysCount, sizeof(unsigned int), 1, filePoint);
	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		fwrite(&m_entrys[index], 8, 1, filePoint);
	}
	fclose(filePoint);
}

IE_END