#define __IE_DLL_EXPORTS__
#include "IECreaturesInfoManager.h"

IE_BEGIN

IECreaturesInfoManager * IECreaturesInfoManager::m_staticCreaturesManager = NULL;

IECreaturesInfoManager::IECreaturesInfoManager()
{
	m_creaturesInfoCount = 0;
}

IECreaturesInfoManager::~IECreaturesInfoManager()
{
	for (unsigned int index = 0; index < m_creaturesInfoCount; index++)
	{
		__IE_RELEASE_DIF__(m_creaturesInfoList[index]._XML);
		__IE_LUA_RELEASE__(m_creaturesInfoList[index]._LuaScript);
	}
	if (m_creaturesInfoList)
	{
		delete[] m_creaturesInfoList;
	}
}

void IECreaturesInfoManager::Initialization()
{
	LoadCreaturesInfo();
}

void IECreaturesInfoManager::Release()
{
	delete this;
}

IECreaturesInfoManager * IECreaturesInfoManager::Share()
{
	if (m_staticCreaturesManager == NULL)
	{
		m_staticCreaturesManager = new IECreaturesInfoManager();
		m_staticCreaturesManager->Initialization();
	}
	return m_staticCreaturesManager;
}

void IECreaturesInfoManager::LoadCreaturesInfo()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["creatureInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	char buf[1024];
	while (fgets(buf, 1024, fp))
	{
		m_creaturesInfoCount++;
	}

	if (m_creaturesInfoCount == 0)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
	m_creaturesInfoList = new IECreatureInfo[m_creaturesInfoCount];

	unsigned int index = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &(m_creaturesInfoList[index]._CreatureID), m_creaturesInfoList[index]._CreatureName);
		
		if (m_creaturesInfoList[index]._CreatureID)
		{
			fileDir = IEString(m_creaturesInfoList[index]._CreatureName) << ".xml";

			m_creaturesInfoList[index]._LuaScript = NULL;
			m_creaturesInfoList[index]._XML = IEXml::Create(fileDir.GetString());

			//Ìî³äÊý¾Ý
			m_creaturesInfoList[index]._CreatureType = (IECreatureType)(m_creaturesInfoList[index]._XML->FindChild("type")->ValueInt());
			m_creaturesInfoList[index]._View = m_creaturesInfoList[index]._XML->FindChild("view")->ValueFloat();
			m_creaturesInfoList[index]._BaseHealth = m_creaturesInfoList[index]._XML->FindChild("baseHealth")->ValueInt();
			m_creaturesInfoList[index]._GrowHealth = m_creaturesInfoList[index]._XML->FindChild("growHealth")->ValueInt();
			m_creaturesInfoList[index]._BaseMagic = m_creaturesInfoList[index]._XML->FindChild("baseMagic")->ValueInt();
			m_creaturesInfoList[index]._GrowMagic = m_creaturesInfoList[index]._XML->FindChild("growMagic")->ValueInt();
			m_creaturesInfoList[index]._BaseSpeed = m_creaturesInfoList[index]._XML->FindChild("baseSpeed")->ValueInt();
			m_creaturesInfoList[index]._GrowSpeed = m_creaturesInfoList[index]._XML->FindChild("growSpeed")->ValueInt();
			m_creaturesInfoList[index]._BaseDamage = m_creaturesInfoList[index]._XML->FindChild("physicDamage")->ValueInt();
			m_creaturesInfoList[index]._GrowDamage = m_creaturesInfoList[index]._XML->FindChild("growPhysicDamage")->ValueInt();
		}
		else
		{
			m_creaturesInfoList[index]._LuaScript = NULL;
			m_creaturesInfoList[index]._XML = NULL;
		}

		index++;
	}

	fclose(fp);
}

void IECreaturesInfoManager::SaveCreaturesInfo()
{
	FILE * filePoint = fopen("./data/creature.txt", "wb");
	for (unsigned int index = 0; index < m_creaturesInfoCount; index++)
	{
		fwrite(&m_creaturesInfoList[index], sizeof(IECreatureInfo), 1, filePoint);
	}
	fclose(filePoint);
}

IE_END