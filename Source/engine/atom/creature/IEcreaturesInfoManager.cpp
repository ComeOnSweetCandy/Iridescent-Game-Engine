#define __IE_DLL_EXPORTS__
#include "IEcreaturesInfoManager.h"

IE_BEGIN

IECreaturesInfoManager * IECreaturesInfoManager::m_staticCreaturesManager = NULL;

IECreaturesInfoManager::IECreaturesInfoManager()
{
	m_creaturesInfoCount = 0;
}

IECreaturesInfoManager::~IECreaturesInfoManager()
{
	for (int index = 0; index < m_creaturesInfoCount; index++)
	{
		delete m_creaturesInfoList[index];
	}
	delete [] m_creaturesInfoList;
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
	IEString infoFileDir = pOBJECT_TO_cSTRING(SETTING["BaseDir"]) + "creature.txt";
	FILE * filePoint = fopen(infoFileDir.GetString(), "r");
	char c;
	while ((c = fgetc(filePoint)) != EOF)
	{
		if (c == '\n')
		{
			m_creaturesInfoCount++;
		}
	}
	m_creaturesInfoCount++;

	fseek(filePoint, 0, SEEK_SET);
	m_creaturesInfoList = new IECreatureInfo *[m_creaturesInfoCount];
	IECreatureInfo * data;
	int index = 0;
	while (!feof(filePoint))
	{
		data = new IECreatureInfo();
		fscanf(filePoint, "%d %s %d %d %d %f", &(data->m_creatureID), data->m_creatureClassName, &(data->m_creatureType), &(data->m_baseHealth), &(data->m_degressHealth), &(data->m_speed));
		m_creaturesInfoList[index] = data;

		index++;
	}
	fclose(filePoint);
}

void IECreaturesInfoManager::SaveCreaturesInfo()
{
	FILE * filePoint = fopen("./data/creature.txt", "wb");
	for (int index = 0; index < m_creaturesInfoCount; index++)
	{
		fwrite(&m_creaturesInfoList[index], sizeof(IECreatureInfo), 1, filePoint);
	}
	fclose(filePoint);
}

IE_END