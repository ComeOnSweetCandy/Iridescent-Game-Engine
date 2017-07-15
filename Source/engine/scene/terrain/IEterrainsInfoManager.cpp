#define __IE_DLL_EXPORTS__
#include "IEterrainsInfoManager.h"

#include "../../../type/IEstring.h"
#include "../../../core/container/IEdictionary.h"
#include "../../../tools/IEtime.h"

IE_BEGIN

IETerrainsInfoManager * IETerrainsInfoManager::m_staticTerrainsManager = NULL;

IETerrainsInfoManager::IETerrainsInfoManager()
{
	m_terrainsInfoList = NULL;
	m_terrainsInfoCount = 0;
}

IETerrainsInfoManager::~IETerrainsInfoManager()
{
	if (m_terrainsInfoList)
	{
		delete[] m_terrainsInfoList;
	}
}

void IETerrainsInfoManager::Initialization()
{
	LoadTerrainsInfo();
}

void IETerrainsInfoManager::Release()
{
	delete this;
}

IETerrainsInfoManager * IETerrainsInfoManager::Share()
{
	if (m_staticTerrainsManager == NULL)
	{
		m_staticTerrainsManager = new IETerrainsInfoManager();
		m_staticTerrainsManager->Initialization();
	}
	return m_staticTerrainsManager;
}

void IETerrainsInfoManager::LoadTerrainsInfo()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["terrainInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	if (!fp)
	{
		__IE_ERROR__("IETerrainsInfoManager : can not read terrain file.\n");
	}

	char buf[1024];
	while (fgets(buf, 1024, fp))
	{
		m_terrainsInfoCount++;
	}

	if (m_terrainsInfoCount == 0)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
	m_terrainsInfoList = new IETerrainInfo[m_terrainsInfoCount];

	unsigned int index = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &(m_terrainsInfoList[index]._TerrainID), m_terrainsInfoList[index]._TerrainName);

		IEString fileDir = IEString(m_terrainsInfoList[index]._TerrainName) << ".xml";

		m_terrainsInfoList[index]._LuaScript = NULL;
		m_terrainsInfoList[index]._PieceC = 1;
		m_terrainsInfoList[index]._BodyC = 1;
		m_terrainsInfoList[index++]._Xml = IEXml::Create(fileDir.GetString());
	}
	
	fclose(fp);
}

void IETerrainsInfoManager::SaveTerrainsInfo()
{
	IEString fileDir = pOBJECT_TO_cSTRING(SETTING["terrainInfoFile"]);
	FILE * fp = fopen(fileDir.GetString(), "r");

	if (!fp)
	{
		__IE_ERROR__("IETerrainsInfoManager : can not read terrain file.\n");
	}

	fwrite(m_terrainsInfoList, sizeof(IETerrainInfo), m_terrainsInfoCount, fp);

	fclose(fp);
}

IETerrainInfo * IETerrainsInfoManager::GetTerrainsInfoList()
{
	return m_terrainsInfoList;
}

unsigned int IETerrainsInfoManager::GetTerrainsInfoCount()
{
	return m_terrainsInfoCount;
}

IE_END