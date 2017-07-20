/***********************************
* name     : IESkillsManager.h
* creater  : cosc
* info     : skill manager
* date     : 2017/6/12
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_SKILL_MANAGER__
#define __IE_SKILL_MANAGER__

#include "../../atom/creature/IEcreatureInfo.h"
#include "../../../core/IEnode.h"
#include "../../trigger/IEtrigger.h"

IE_BEGIN

enum IESkillType
{
	__ie_skill_self__,
	__ie_skill_prop__
};

typedef struct _ieSkillInfo
{
	unsigned int _SkillID;
	IESkillType _SkillType;
	char _SkillName[256];

	lua_State * _Script;
}IESkillInfo;

class __IE_DLL__ IESkillsManager :public IEObject
{
public:
	IESkillsManager();
	virtual ~IESkillsManager();
	virtual void Initialization();
	static IESkillsManager * Share();

private:
	void ReadSkills();

private:
	static IESkillsManager * m_staticSkillManager;

	IESkillInfo * m_skillsList;
};

IE_END

#endif