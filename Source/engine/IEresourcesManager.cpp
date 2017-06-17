#define __IE_DLL_EXPORTS__
#include "IEresourcesManager.h"

#include "../core/container/IEautoReleasePool.h"
#include "atom/creature/IEcreaturesInfoManager.h"
#include "atom/prop/IEpropsInfoManager.h"
#include "scene/terrain/IEterrainsInfoManager.h"
#include "scene/thing/IEthingsInfoManager.h"

#include "../control/IEinputManager.h"
#include "../tools/IEtime.h"
#include "../core/IEcamera.h"

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
	IETerrainsInfoManager::Share()->Release();				//������Ϣ��Դ
	IEAdorningsInfoManager::Share()->Release();				//װ����Ϣ��Դ
	IECamera::Share()->Release();							//����ͷ�

	//ϵͳ��Դ
	IESettingDictionary::Share()->Release();				//ϵͳ�趨��Դ
	IEInputManager::Share()->Release();						//���������ͷ�
	IETime::Share()->Release();								//ʱ���ͷ�
}

void IEResourcesManager::Initialization()
{
	IESettingDictionary::Share();
	IEResourcesDictionary::Share();

	IECreaturesInfoManager::Share();
	IETerrainsInfoManager::Share();
	IEAdorningsInfoManager::Share();
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
	IECamera::Share()->Run();
	IEAutoReleasePool::Share()->Run();
}

IE_END