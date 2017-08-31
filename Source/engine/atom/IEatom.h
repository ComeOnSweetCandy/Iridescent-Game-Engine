/***********************************
* name     : IEAtom.h
* creater  : cosc
* info     : everthing in this world were based atom
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
	virtual void Update();				//ÿ��ˢ��

	virtual void Born();				//ÿһ֡�Ĵ���
	virtual void Live();				//liveʱ�Ĵ���
	virtual void Die();					//dieʱ�Ĵ���

public:
	virtual void ChangeState(unsigned stateIndex);

	void SetTextureGroupName(const char * name);
	const char * GetTextureGroupName();

	lua_State * GetLuaScript();

protected:
	IEString m_textureGroupName;
	lua_State * m_script;
	IEXml * m_XML;

	//��ʾ��ǰ��״̬��ż����״ֵ̬
	unsigned int m_curStateIndex;
	unsigned int m_maxStateCount;
};

IE_END

#endif