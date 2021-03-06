#ifndef __IE__
#define __IE__

//global
#include "global/IEstdafx.h"

//thread
#include "thread/IEthread.h"

//tools
#include "tools/IEtime.h"
#include "tools/IEfontTTF.h"
#include "tools/IEfile.h"
#include "tools/IETexturePacker.h"
#include "tools/IEXml.h"
#include "tools/IEPackerTexture.h"

//type
#include "type/IEstring.h"
#include "type/IEbaseType.h"

//interface
#include "interface/cmd/IEframe.h"
#include "interface/cmd/IEapplication.h"
#include "interface/win32/IEWin32application.h"

//core
#include "core/container/IEautoReleasePool.h"
#include "core/container/IEdictionary.h"
#include "core/container/IEstack.h"
#include "core/IEcamera.h"

//action
#include "core/animation/IEmoveTo.h"
#include "core/animation/IEscaleBy.h"
#include "core/animation/IEwander.h"
#include "core/animation/IEsynchronizeAnimation.h"

//element
#include "core/IEnode.h"
#include "core/element/IEsprite.h"
#include "core/shader/IEshader.h"
#include "core/element/IEschizo.h"
#include "core/element/IEprocessBar.h"
#include "core/element/IEtext.h"

//thread
#include "thread/IEthread.h"
#include "thread/IEconsole.h"

#include "tools/IEfontTTF.h"

//controll
#include "control/IEinputManager.h"


//physic
#include "physic/IEphysicWorld.h"
#include "physic/IEphysicNode.h"
#include "physic/IEphysicEdgeCollision.h"

//engine
#include "engine/scene/terrain/IETerrainArea.h"
#include "engine/scene/thing/IEthingArea.h"

//terrain
#include "engine/scene/IEmap.h"
#include "engine/scene/IEtotalScene.h"
#include "engine/scene/terrain/items/IEwater.h"

//atom
#include "engine/atom/creature/IECreature.h"
#include "engine/atom/creature/IEplayer.h"
#include "engine/atom/creature/IEArmer.h"
#include "engine/atom/creature/IECreatureList.h"
#include "engine/atom/prop/IEPropPack.h"

//trigger
#include "engine/trigger/IEtrigger.h"

//prop
#include "engine/atom/prop/IEProp.h"

//ai
#include "ai/IEPathFinder.h"

//thing
#include "engine/scene/thing/items/IETorch.h"
//#include "engine/scene/thing/items/IEDoorInteraction.h"

//particle
#include "core/particle/IEray.h"

#endif