/***********************************
* name     : IEPlayer.h
* creater  : cosc
* info     : keyboard from player
* date     : 2016/12/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PLAYER__
#define __IE_PLAYER__

#include "IECreature.h"
#include "IEArmer.h"
#include "../../../control/IEplayerNode.h"
#include "../prop/IEpropPack.h"

IE_BEGIN

class __IE_DLL__ IEPlayer :public IEArmer, public IEPlayerNode
{
public:
	IEPlayer();
	virtual ~IEPlayer();
	virtual void Initialization(int creatureID);
	static IEPlayer * Create(int creatureID);

public:
	virtual void Live();
	virtual void BindPlayerControl();
	virtual void PlayerPressKeyA(unsigned char key);
	virtual void PlayerPressKeyD(unsigned char key);
	virtual void PlayerPressKeyW(unsigned char key);
	virtual void PlayerPressKeyS(unsigned char key);
	virtual void PlayerPressKeyJ(unsigned char key);
	virtual void PlayerPressKeyK(unsigned char key);
	virtual void PlayerPressNumberKey(unsigned char key);

	virtual void HandlePlayerControll();			//处理所有用户的操作
	virtual void ResetEverything();					//所有操作初始化

public:
	IEPropPack * GetPlayersPack();

private:
	IEGrid m_moveDirection;
	bool m_attack;
	bool m_jump;

	IEAction * m_nextAction;
	IEPropPack * m_propPack;
};

IE_END

#endif