/***********************************
* name     : IEplayerNode.h
* creater  : cosc
* info     : keyboard from player
* date     : 2016/12/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_PLAYER_NODE__
#define __IE_PLAYER_NODE__

#include "../core/IEnode.h"
#include "IEkeyboard.h"

IE_BEGIN

class __IE_DLL__ IEPlayerNode
{
public:
	IEPlayerNode();
	~IEPlayerNode();

public:
	virtual void BindPlayerControl(){};
	virtual void PlayerPressKeyW();
	virtual void PlayerPressKeyA();
	virtual void PlayerPressKeyS();
	virtual void PlayerPressKeyD();

private:

};

IE_END

#endif