#define __IE_DLL_EXPORTS__
#include "IEpropsInfoManager.h"

#include "../../../core/container/IEdictionary.h"
#include "../../../type/IEstring.h"

IE_BEGIN

IEPropsInfoManager * IEPropsInfoManager::m_propsInfoManager = NULL;

IEPropsInfoManager::IEPropsInfoManager()
{
	m_propsInfoCount = 0;
}

IEPropsInfoManager::~IEPropsInfoManager()
{
	delete []m_propsInfoList;
}

void IEPropsInfoManager::Initialization()
{
	LoadPropInfos();
}

void IEPropsInfoManager::Release()
{
	delete this;
}

IEPropsInfoManager * IEPropsInfoManager::Share()
{
	if (m_propsInfoManager == NULL)
	{
		m_propsInfoManager = new IEPropsInfoManager();
		m_propsInfoManager->Initialization();
	}
	return m_propsInfoManager;
}

void IEPropsInfoManager::LoadPropInfos()
{
	IEString infoFileDir = pOBJECT_TO_cSTRING(SETTING["BaseDir"]) + "prop.info";
	FILE * file = fopen(infoFileDir.GetString(), "r");

	char c;
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			m_propsInfoCount++;
		}
	}
	m_propsInfoCount++;

	fseek(file, 0, SEEK_SET);
	m_propsInfoList = new IEPropInfo[m_propsInfoCount];

	int index = 0;
	while (!feof(file))
	{
		fscanf(file, "%d %s", &(m_propsInfoList[index].s_index), m_propsInfoList[index].s_name);

		index++;
	}
	fclose(file);
}

IEPropInfo& IEPropsInfoManager::LoadPropInfo(unsigned int propInfoIndex)
{
	for (unsigned int index = 0; index < m_propsInfoCount; index++)
	{
		if (m_propsInfoList[index].s_index == propInfoIndex)
		{
			return m_propsInfoList[index];
		}
	}

	return m_propsInfoList[0];
}

IE_END