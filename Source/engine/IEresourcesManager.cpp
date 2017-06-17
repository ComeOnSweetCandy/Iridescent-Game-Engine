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
	//游戏内资源文件
	IEAutoReleasePool::Share()->Release();					//自动释放池
	IEResourcesDictionary::Share()->Release();				//贴图着色器资源
	IECreaturesInfoManager::Share()->Release();				//人物信息资源
	IEPropsInfoManager::Share()->Release();					//道具信息资源
	IETerrainsInfoManager::Share()->Release();				//地形信息资源
	IEAdorningsInfoManager::Share()->Release();				//装饰信息资源
	IECamera::Share()->Release();							//相机释放

	//系统资源
	IESettingDictionary::Share()->Release();				//系统设定资源
	IEInputManager::Share()->Release();						//操作功能释放
	IETime::Share()->Release();								//时间释放
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