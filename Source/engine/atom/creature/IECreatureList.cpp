#define __IE_DLL_EXPORTS__
#include "IECreatureList.h"

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
	}
}

void IECreatureList::Initialization()
{
	LoadCreaturesInfo();
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

void IECreatureList::LoadList()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["creatureInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	char buf[1024];
	while (fgets(buf, 1024, fp))
	{
		m_entrysCount++;
	}

	if (m_entrysCount == 0)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
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

			//Ìî³äÊý¾Ý
			IEXml * propertyXML = m_entrys[index]._XML->FindChild("property");

			m_entrys[index]._CreatureType = (IECreatureType)(propertyXML->FindChild("type")->ValueInt());
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

void IECreatureList::SaveCreaturesInfo()
{
	FILE * filePoint = fopen("./data/creature.txt", "wb");
	for (unsigned int index = 0; index < m_entrysCount; index++)
	{
		fwrite(&m_entrys[index], sizeof(IECreatureEntry), 1, filePoint);
	}
	fclose(filePoint);
}

IE_END