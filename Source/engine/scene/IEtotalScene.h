/***********************************
* name     : IEtotalScene.h
* creater  : cosc
* info     : only scene
* date     : 2017/3/28
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_TOTAL_SCENE__
#define __IE_TOTAL_SCENE__

#include "../../core/IEscene.h"
#include "../../physic/IEphysicWorld.h"
#include "prop/IEpropLayer.h"
#include "IEDrawScene.h"
#include "IEmap.h"
#include "../atom/creature/IEplayer.h"

IE_BEGIN

class __IE_DLL__ IETotalScene :public IEScene
{
public:
	IETotalScene();
	virtual ~IETotalScene();
	virtual void Initialization(char * sceneName);
	static IETotalScene * CreateAndRetain(char * sceneName);

public:
	virtual void Run();
	virtual void AddChild(IECreature * creature);
	virtual void AddChild(IEPlayer * player);

	IETriggerManager * GetTriggerManager();
	IEPhysicWorld * GetPhysicWorld();
	IELayer * GetPropLayer();
	IEMap * GetBindedMap();
	IEContainer * GetCreatures();
	IEPlayer * GetPlayer();

private:
	IETriggerManager * m_triggerManager;
	IEPhysicWorld * m_physicWorld;
	IELayer * m_propLayer;
	IEMap * m_map;
	IELayer * m_creaturesLayer;
	IEPlayer * m_player;
	IEDrawScene * m_drawScene;			//—”≥Ÿ‰÷»æ ª˘”⁄z÷·À˜“˝∞¥–Ú‰÷»æ
};

IE_END

#endif