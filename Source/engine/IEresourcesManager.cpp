#define __IE_DLL_EXPORTS__
#include "IEresourcesManager.h"

#include "../core/container/IEautoReleasePool.h"
#include "atom/creature/IEcreaturesInfoManager.h"
#include "atom/prop/IEpropsInfoManager.h"
#include "scene/terrain/IETerrainList.h"
#include "scene/thing/IEThingList.h"

#include "../control/IEinputManager.h"
#include "../tools/IEtime.h"
#include "../core/IEcamera.h"

#include "../thread/IEconsole.h"
#include "../tools/IEcmdAnalyse.h"

IE_BEGIN

IEResourcesManager::IEResourcesManager()
{

}

IEResourcesManager::~IEResourcesManager()
{
	//��Ϸ����Դ�ļ�
	IEAutoReleasePool::Share()->Release();					//�Զ��ͷų�
	IEResourcesDictionary::Share()->Release();				//��ͼ��ɫ����Դ
	IECreaturesInfoManager::Share()->Release();				//������Ϣ��Դ
	IEPropsInfoManager::Share()->Release();					//������Ϣ��Դ
	IETerrainList::Share()->Release();				//������Ϣ��Դ
	IEThingList::Share()->Release();				//װ����Ϣ��Դ
	IECamera::Share()->Release();							//����ͷ�

	//ϵͳ��Դ
	IESettingDictionary::Share()->Release();				//ϵͳ�趨��Դ
	IESituation::Share()->Release();						//ɾ����������
	IEInputManager::Share()->Release();						//���������ͷ�
	IETime::Share()->Release();								//ʱ���ͷ�
	
	//����
	IECmdAnalyse::Share()->Release();						//�ͷ����������
	IEConsole::Share()->Release();							//�ͷſ���̨
}

void IEResourcesManager::Initialization()
{
	IESettingDictionary::Share();
	IEResourcesDictionary::Share();

	IECreaturesInfoManager::Share();
	IETerrainList::Share();
	IEThingList::Share();

	IEConsole::Share()->Initialization();
}

IEResourcesManager * IEResourcesManager::CreateAndRetain()
{
	IEResourcesManager * resources = new IEResourcesManager();
	resources->Initialization();
	resources->Retain();
	return resources;
}

void IEResourcesManager::Run()
{
	IETime::Share()->Run();
	IEInputManager::Share()->Run();
	IEAutoReleasePool::Share()->Run();
	IECmdAnalyse::Share()->Run();
}

IE_END