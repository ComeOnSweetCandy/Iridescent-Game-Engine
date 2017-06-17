#define __IE_DLL_EXPORTS__
#include "IESkillsManager.h"

IE_BEGIN

IESkillsManager * IESkillsManager::m_staticSkillManager = NULL;

IESkillsManager::IESkillsManager()
{
	m_skillsList = NULL;
}

IESkillsManager::~IESkillsManager()
{

}

void IESkillsManager::Initialization()
{

}

IESkillsManager * IESkillsManager::Share()
{
	if (m_staticSkillManager == NULL)
	{
		m_staticSkillManager = new IESkillsManager();
		m_staticSkillManager->Initialization();
	}
	return m_staticSkillManager;
}

void IESkillsManager::ReadSkills()
{
	FILE * fp = fopen("../Debug/data/skill.txt", "r");
	IESkillInfo cache;
	unsigned int count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %s %s", &(cache._SkillID), &(cache._SkillType), cache._SkillName);
		count++;
	}
	fseek(fp, 0, SEEK_SET);

	m_skillsList = new IESkillInfo[count];
	for (unsigned int index = 0; index < count; index++)
	{
		fscanf(fp, "%d %d %s %s", &(m_skillsList[index]._SkillID), &(m_skillsList[index]._SkillType), m_skillsList[index]._SkillName);
	}

	fclose(fp);
}

IE_END