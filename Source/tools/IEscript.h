/***********************************
* name     : IEscript.h
* creater  : cosc
* info     : lua script
* date     : 2017/5/10
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SCRIPT__
#define __IE_SCRIPT__

#include "../core/IEobject.h"

IE_BEGIN

class __IE_DLL__ IEScript :public IEObject
{
public:
	IEScript();
	virtual ~IEScript();
	virtual void Initialization(const char * scriptName);
	static IEScript * Create(const char * scriptName);

public:
	void SetLuaScript(lua_State * luaScript);
	lua_State * GetLuaScript();

private:
	lua_State * m_script;
};

IE_END

#endif