#define __IE_DLL_EXPORTS__
#include "IEresourcesManager.h"

#include "../core/container/IEautoReleasePool.h"
#include "atom/creature/IECreatureList.h"
#include "atom/prop/IEPropList.h"
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
	//游戏内资源文件
	IEAutoReleasePool::Share()->Release();					//自动释放池
	IEResourcesDictionary::Share()->Release();				//贴图着色器资源
	IECreatureList::Share()->Release();						//人物信息资源
	IEPropList::Share()->Release();					//道具信息资源
	IETerrainList::Share()->Release();						//地形信息资源
	IEThingList::Share()->Release();						//装饰信息资源
	IECamera::Share()->Release();							//相机释放

	//系统资源
	IESettingDictionary::Share()->Release();				//系统设定资源
	IESituation::Share()->Release();						//删除环境变量
	IEInputManager::Share()->Release();						//操作功能释放
	IETime::Share()->Release();								//时间释放
	
	//额外
	IECmdAnalyse::Share()->Release();						//释放命令解析器
	IEConsole::Share()->Release();							//释放控制台
}

void IEResourcesManager::Initialization()
{
	IESettingDictionary::Share();
	IEResourcesDictionary::Share();

	IECreatureList::Share();
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