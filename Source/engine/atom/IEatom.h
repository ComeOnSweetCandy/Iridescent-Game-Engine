/***********************************
* name     : IEatom.h
* creater  : cosc
* info     : everthing in this world were called atom
* date     : 2016/12/18
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_ATOM__
#define __IE_ATOM__

#include "../../core/element/IEsprite.h"
#include "../../physic/IEphysicNode.h"
#include "creature/action/IEActionMachine.h"

IE_BEGIN

class __IE_DLL__ IEAtom:public IESprite
{                              
public:
	IEAtom();
	virtual ~IEAtom();
	virtual void Initialization();
	static IEAtom * Create();

protected:
	virtual void Update();

	virtual void Born();
	virtual void Live();
	virtual void Die();

public:
	void SetTextureGroupName(const char * name);
	const char * GetTextureGroupName();

	lua_State * GetLuaScript();

protected:
	IEString m_textureGroupName;
	lua_State * m_luaScript;
};

IE_END

#endif