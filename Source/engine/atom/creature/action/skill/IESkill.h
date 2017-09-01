/***********************************
* name     : IEskill.h
* creater  : cosc
* info     : skill base
* date     : 2017/6/12
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SKILL__
#define __IE_SKILL__

#include "IESkillsManager.h"

IE_BEGIN

class __IE_DLL__ IESkill
{
public:
	IESkill();
	virtual ~IESkill();
	virtual void Initialization();
	virtual void Release();
	static IESkill * Create();

protected:
	virtual bool Begin() = 0;
	virtual bool Excute() = 0;
	virtual bool End() = 0;

	void LoadLUA();

private:
	IESkillType m_skillType;
	unsigned int m_skillID;
	unsigned char m_skillLevel;

	lua_State * m_script;
};

IE_END

#endif